# Developer Documentation

Technical documentation for developers working on the Inception project.

## Table of Contents

1. [Environment Setup](#environment-setup)
2. [Project Structure](#project-structure)
3. [Docker Architecture](#docker-architecture)
4. [Service Details](#service-details)
5. [Networking](#networking)
6. [Volume Management](#volume-management)
7. [Build Process](#build-process)
8. [SSL Certificate Generation](#ssl-certificate-generation)
9. [Development Workflow](#development-workflow)
10. [Debugging](#debugging)
11. [Command Reference](#command-reference)

## Environment Setup

### Prerequisites Installation

```bash
# Update system
sudo apt update && sudo apt upgrade -y

# Install Docker
sudo apt install -y apt-transport-https ca-certificates curl gnupg
curl -fsSL https://download.docker.com/linux/debian/gpg | \
  sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg
echo "deb [arch=amd64 signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] \
  https://download.docker.com/linux/debian $(lsb_release -cs) stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list
sudo apt update
sudo apt install -y docker-ce docker-ce-cli containerd.io docker-compose-plugin

# Add user to docker group
sudo usermod -aG docker $USER
newgrp docker
```

### Environment Configuration

Create `srcs/.env`:

```bash
# Domain Configuration
DOMAIN_NAME=corin.42.fr

# MariaDB Configuration
MYSQL_ROOT_PASSWORD=secure_root_password
MYSQL_DATABASE=wordpress
MYSQL_USER=wpuser
MYSQL_PASSWORD=secure_user_password

# WordPress Configuration
WP_ADMIN_USER=admin_user
WP_ADMIN_PASSWORD=secure_admin_password
WP_ADMIN_EMAIL=admin@example.com
WP_USER=regular_user
WP_USER_EMAIL=user@example.com
WP_USER_PASSWORD=secure_user_password
WP_TITLE=My Inception Site
WP_URL=https://corin.42.fr
```

## Project Structure

```
inception/
├── Makefile                      # Build automation + SSL generation
├── README.md                     # Project overview
├── USER_DOC.md                   # User documentation
├── DEV_DOC.md                    # Developer documentation
├── .gitignore                    # Git exclusions
└── srcs/
    ├── docker-compose.yml        # Container orchestration
    ├── .env                      # Environment variables
    └── requirements/
        ├── mariadb/
        │   ├── Dockerfile        # MariaDB image definition
        │   ├── .dockerignore
        │   ├── conf/
        │   │   └── 50-server.cnf # MariaDB configuration
        │   └── tools/
        │       └── init-db.sh    # Database initialization
        ├── wordpress/
        │   ├── Dockerfile        # WordPress image definition
        │   ├── .dockerignore
        │   ├── conf/
        │   │   └── www.conf      # PHP-FPM pool configuration
        │   └── tools/
        │       └── setup-wordpress.sh # WordPress setup script
        └── nginx/
            ├── Dockerfile        # NGINX image definition
            ├── .dockerignore
            ├── conf/
            │   └── nginx.conf    # NGINX configuration
            └── tools/
                ├── nginx.crt     # SSL cert (auto-generated)
                └── nginx.key     # SSL key (auto-generated)
```

## Docker Architecture

### Container Communication Flow

```
Internet (HTTPS)
      ↓
   Port 443
      ↓
┌──────────────┐
│    NGINX     │ (Reverse proxy, TLS termination)
│  Container   │
└──────┬───────┘
       │ FastCGI (port 9000)
       ↓
┌──────────────┐
│  WordPress   │ (PHP-FPM)
│  Container   │
└──────┬───────┘
       │ MySQL Protocol (port 3306)
       ↓
┌──────────────┐
│   MariaDB    │ (Database)
│  Container   │
└──────────────┘
```

### Network Isolation

- **Docker Network:** `inception` (bridge driver)
- **Service Discovery:** Containers communicate using service names
- **Port Exposure:** Only NGINX exposes port 443 to host
- **Internal Communication:** WordPress ↔ MariaDB via internal network

## Service Details

### MariaDB Container

**Dockerfile Breakdown:**

```dockerfile
FROM debian:bullseye              # Base image (Debian 11)

RUN apt-get update && \           # Update package list
    apt-get install -y \          # Install packages
    mariadb-server \              # MariaDB server
    mariadb-client \              # MariaDB client tools
    && rm -rf /var/lib/apt/lists/* # Clean up to reduce image size

COPY conf/50-server.cnf \         # Copy configuration
     /etc/mysql/mariadb.conf.d/50-server.cnf
COPY tools/init-db.sh \           # Copy init script
     /usr/local/bin/
RUN chmod +x /usr/local/bin/init-db.sh # Make executable

EXPOSE 3306                       # Expose MySQL port (internal only)

ENTRYPOINT ["/usr/local/bin/init-db.sh"] # Run on container start
```

**Configuration (50-server.cnf):**

```ini
[mysqld]
user = mysql                      # Run as mysql user
port = 3306                       # Listen on port 3306
bind-address = 0.0.0.0            # Accept connections from any IP
datadir = /var/lib/mysql          # Data directory
socket = /run/mysqld/mysqld.sock  # Unix socket location
```

**Initialization Script (init-db.sh):**

```bash
#!/bin/bash
set -e                            # Exit on error

mkdir -p /run/mysqld              # Create socket directory
chown -R mysql:mysql /run/mysqld  # Set ownership

# Initialize database if first run
if [ ! -d "/var/lib/mysql/mysql" ]; then
    mysql_install_db --user=mysql --datadir=/var/lib/mysql
fi

# Bootstrap mode: create database and users
mysqld --user=mysql --bootstrap << EOF
USE mysql;
FLUSH PRIVILEGES;
ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${MYSQL_USER}'@'%';
FLUSH PRIVILEGES;
EOF

# Start MySQL in foreground
exec mysqld --user=mysql --console
```

**Key Commands:**
- `mysql_install_db`: Initializes MariaDB data directory
- `mysqld --bootstrap`: Runs SQL without networking for setup
- `exec mysqld`: Replaces shell process (PID 1) with mysqld

### WordPress Container

**Dockerfile Breakdown:**

```dockerfile
FROM debian:bullseye              # Base image

RUN apt-get update && \
    apt-get install -y \
    php7.4-fpm \                  # PHP FastCGI Process Manager
    php7.4-mysql \                # MySQL extension for PHP
    php7.4-curl \                 # cURL support
    php7.4-gd \                   # Image manipulation
    php7.4-xml \                  # XML support
    php7.4-mbstring \             # Multibyte string support
    php7.4-zip \                  # ZIP archive support
    curl \                        # Download tool
    mariadb-client \              # MySQL client for health checks
    && rm -rf /var/lib/apt/lists/*

# Install WP-CLI (WordPress command-line tool)
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && \
    chmod +x wp-cli.phar && \
    mv wp-cli.phar /usr/local/bin/wp

COPY conf/www.conf /etc/php/7.4/fpm/pool.d/www.conf
COPY tools/setup-wordpress.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/setup-wordpress.sh

WORKDIR /var/www/html             # Set working directory

EXPOSE 9000                       # FastCGI port

ENTRYPOINT ["/usr/local/bin/setup-wordpress.sh"]
```

**PHP-FPM Configuration (www.conf):**

```ini
[www]
user = www-data                   # Run as www-data user
group = www-data
listen = 9000                     # Listen on port 9000 (all interfaces)
listen.owner = www-data
listen.group = www-data
pm = dynamic                      # Dynamic process management
pm.max_children = 5               # Maximum child processes
pm.start_servers = 2              # Starting number of children
pm.min_spare_servers = 1          # Minimum idle servers
pm.max_spare_servers = 3          # Maximum idle servers
clear_env = no                    # Pass environment variables to PHP
```

**Setup Script (setup-wordpress.sh):**

```bash
#!/bin/bash
set -e

cd /var/www/html

# Wait for MariaDB to be ready
until mysqladmin ping -h mariadb -u${MYSQL_USER} -p${MYSQL_PASSWORD} --silent; do
    sleep 2
done

# Download and configure WordPress (only on first run)
if [ ! -f wp-config.php ]; then
    wp core download --allow-root
    
    wp config create \
        --dbname=${MYSQL_DATABASE} \
        --dbuser=${MYSQL_USER} \
        --dbpass=${MYSQL_PASSWORD} \
        --dbhost=mariadb:3306 \      # Use container name for DNS
        --allow-root
    
    wp core install \
        --url=${WP_URL} \
        --title="${WP_TITLE}" \
        --admin_user=${WP_ADMIN_USER} \
        --admin_password=${WP_ADMIN_PASSWORD} \
        --admin_email=${WP_ADMIN_EMAIL} \
        --skip-email \
        --allow-root
    
    wp user create ${WP_USER} ${WP_USER_EMAIL} \
        --user_pass=${WP_USER_PASSWORD} \
        --role=author \
        --allow-root
fi

chown -R www-data:www-data /var/www/html

# Start PHP-FPM
mkdir -p /run/php
exec php-fpm7.4 -F                # -F = foreground mode
```

### NGINX Container

**Dockerfile:**

```dockerfile
FROM debian:bullseye

RUN apt-get update && \
    apt-get install -y nginx && \
    rm -rf /var/lib/apt/lists/*

RUN mkdir -p /etc/nginx/ssl       # Create SSL directory

COPY conf/nginx.conf /etc/nginx/nginx.conf
COPY tools/nginx.crt /etc/nginx/ssl/nginx.crt
COPY tools/nginx.key /etc/nginx/ssl/nginx.key

RUN chmod 644 /etc/nginx/ssl/nginx.crt && \
    chmod 600 /etc/nginx/ssl/nginx.key   # Secure private key

EXPOSE 443

CMD ["nginx", "-g", "daemon off;"] # Run in foreground
```

**NGINX Configuration:**

```nginx
events {
    worker_connections 1024;      # Max simultaneous connections
}

http {
    include /etc/nginx/mime.types; # File type mappings
    default_type application/octet-stream;

    sendfile on;                   # Efficient file transfer
    keepalive_timeout 65;

    server {
        listen 443 ssl;            # HTTPS port
        listen [::]:443 ssl;       # IPv6
        
        server_name corin.42.fr;

        # TLS Configuration
        ssl_certificate /etc/nginx/ssl/nginx.crt;
        ssl_certificate_key /etc/nginx/ssl/nginx.key;
        ssl_protocols TLSv1.2 TLSv1.3;
        ssl_prefer_server_ciphers on;

        root /var/www/html;
        index index.php index.html index.htm;

        # Try file, then directory, then pass to PHP
        location / {
            try_files $uri $uri/ /index.php?$args;
        }

        # PHP file handling
        location ~ \.php$ {
            include fastcgi_params;
            fastcgi_pass wordpress:9000;  # Forward to WordPress container
            fastcgi_index index.php;
            fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
            fastcgi_param PATH_INFO $fastcgi_path_info;
        }
    }
}
```

## Networking

### Docker Network

**Created by docker-compose.yml:**

```yaml
networks:
  inception:
    driver: bridge                # Bridge network driver
```

**Benefits:**
- Isolated network namespace
- DNS-based service discovery (e.g., `mariadb` resolves to container IP)
- Automatic IPAM (IP Address Management)

**Testing connectivity:**

```bash
# From WordPress to MariaDB
docker exec wordpress ping -c 3 mariadb

# From NGINX to WordPress
docker exec nginx ping -c 3 wordpress
```

## Volume Management

### Volume Configuration

```yaml
volumes:
  mariadb_data:
    driver: local
    driver_opts:
      type: none                  # Use bind mount
      device: /home/corin/data/mariadb  # Host path
      o: bind                     # Mount option
  wordpress_data:
    driver: local
    driver_opts:
      type: none
      device: /home/corin/data/wordpress
      o: bind
```

**How it works:**
1. Docker creates named volumes (`mariadb_data`, `wordpress_data`)
2. Volumes bind to specific host directories
3. Data persists even when containers are removed
4. Containers mount volumes at specified paths

**Inspecting volumes:**

```bash
docker volume ls
docker volume inspect srcs_mariadb_data
docker volume inspect srcs_wordpress_data
```

## Build Process

### Makefile Explained

```makefile
# Variables
DOCKER_COMPOSE = docker compose -f srcs/docker-compose.yml
DATA_DIR = /home/${USER}/data
CERT_DIR = srcs/requirements/nginx/tools
CERT_KEY = $(CERT_DIR)/nginx.key
CERT_CRT = $(CERT_DIR)/nginx.crt
DOMAIN = ${USER}.42.fr

# Generate SSL certificates if they don't exist
certs:
	@if [ ! -f $(CERT_KEY) ] || [ ! -f $(CERT_CRT) ]; then \
		mkdir -p $(CERT_DIR); \
		openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
			-keyout $(CERT_KEY) \
			-out $(CERT_CRT) \
			-subj "/C=NL/ST=North-Holland/L=Amsterdam/O=42Network/OU=42/CN=$(DOMAIN)"; \
	fi

# Build and start containers (depends on certs)
up: certs
	@mkdir -p $(DATA_DIR)/mariadb
	@mkdir -p $(DATA_DIR)/wordpress
	@$(DOCKER_COMPOSE) up -d --build

# Full clean: remove data and certificates
fclean: clean
	@sudo rm -rf $(DATA_DIR)/mariadb
	@sudo rm -rf $(DATA_DIR)/wordpress
	@rm -f $(CERT_KEY) $(CERT_CRT)  # Remove certificates
	@docker volume rm srcs_mariadb_data srcs_wordpress_data || true
```

**Key features:**
- `up` depends on `certs` - certificates generated automatically
- `fclean` removes certificates along with data
- Idempotent certificate generation (checks if files exist)

### Build Order

**docker-compose.yml dependency chain:**

```yaml
mariadb:                          # Built first (no dependencies)
  ...

wordpress:
  depends_on:
    - mariadb                     # Built after mariadb

nginx:
  depends_on:
    - wordpress                   # Built after wordpress
```

**Build steps:**
1. Makefile checks for SSL certificates
2. Generates certificates if missing
3. Docker builds MariaDB image
4. Docker builds WordPress image
5. Docker builds NGINX image
6. Containers start in dependency order
7. Health checks validate services

## SSL Certificate Generation

### Automatic Generation Process

**How it works:**

1. **Makefile target `certs`:**
```makefile
certs:
	@if [ ! -f $(CERT_KEY) ] || [ ! -f $(CERT_CRT) ]; then
		# Only runs if certificates don't exist
		openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
			-keyout $(CERT_KEY) \
			-out $(CERT_CRT) \
			-subj "/C=NL/ST=North-Holland/L=Amsterdam/O=42Network/OU=42/CN=$(DOMAIN)"
	fi
```

2. **up target depends on certs:**
```makefile
up: certs
	# Certificates are guaranteed to exist before building
```

3. **Dockerfile copies certificates:**
```dockerfile
COPY tools/nginx.crt /etc/nginx/ssl/nginx.crt
COPY tools/nginx.key /etc/nginx/ssl/nginx.key
```

### Certificate Details

**Command breakdown:**
```bash
openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
  -keyout nginx.key \
  -out nginx.crt \
  -subj "/C=NL/ST=North-Holland/L=Amsterdam/O=42Network/OU=42/CN=corin.42.fr"
```

- `req`: Certificate request utility
- `-x509`: Generate self-signed certificate
- `-nodes`: No DES encryption (no passphrase)
- `-days 365`: Valid for 1 year
- `-newkey rsa:2048`: Generate 2048-bit RSA key
- `-keyout`: Private key output file
- `-out`: Certificate output file
- `-subj`: Certificate subject (bypasses interactive prompts)

**Subject fields:**
- C = Country (NL)
- ST = State (North-Holland)
- L = Locality (Amsterdam)
- O = Organization (42Network)
- OU = Organizational Unit (42)
- CN = Common Name (corin.42.fr) - **MUST match domain**

### Manual Certificate Regeneration

```bash
# Regenerate certificates
make fclean  # Removes old certificates
make certs   # Generates new ones

# Or manually
rm -f srcs/requirements/nginx/tools/nginx.{crt,key}
make certs
```

## Development Workflow

### Making Changes

**1. Modify configuration:**

```bash
nano srcs/requirements/nginx/conf/nginx.conf
```

**2. Rebuild specific service:**

```bash
docker compose -f srcs/docker-compose.yml up -d --build nginx
```

**3. View logs:**

```bash
docker logs -f nginx
```

### Testing Changes

```bash
# Test NGINX config
docker exec nginx nginx -t

# Test MariaDB connection
docker exec mariadb mysqladmin ping -p

# Test WordPress
docker exec wordpress wp --info --allow-root

# Access container shell
docker exec -it nginx bash
docker exec -it wordpress bash
docker exec -it mariadb bash
```

## Debugging

### Common Debugging Commands

```bash
# View all container logs
docker compose -f srcs/docker-compose.yml logs

# Follow specific service logs
docker logs -f mariadb
docker logs -f wordpress --tail=100

# Inspect container
docker inspect mariadb

# View container processes
docker top wordpress

# Check resource usage
docker stats

# Network inspection
docker network inspect srcs_inception

# Execute commands in container
docker exec mariadb ps aux
docker exec wordpress ls -la /var/www/html
```

### Debugging SSL Issues

```bash
# Check certificates exist
ls -la srcs/requirements/nginx/tools/

# Verify certificate details
openssl x509 -in srcs/requirements/nginx/tools/nginx.crt -text -noout

# Check certificate validity
openssl x509 -in srcs/requirements/nginx/tools/nginx.crt -noout -dates

# Test TLS connection
openssl s_client -connect localhost:443 -servername corin.42.fr
```

### Debugging MariaDB

```bash
# Enter database
docker exec -it mariadb mysql -u root -p

# Run queries
SHOW DATABASES;
USE wordpress;
SHOW TABLES;
SELECT * FROM wp_users;
```

### Debugging WordPress

```bash
# Check WordPress status
docker exec wordpress wp core version --allow-root
docker exec wordpress wp plugin list --allow-root
docker exec wordpress wp theme list --allow-root

# Check PHP errors
docker exec wordpress tail -f /var/log/php7.4-fpm.log
```

### Debugging NGINX

```bash
# Test configuration
docker exec nginx nginx -t

# Check access logs
docker exec nginx tail -f /var/log/nginx/access.log

# Check error logs
docker exec nginx tail -f /var/log/nginx/error.log

# Reload config without restart
docker exec nginx nginx -s reload
```

## Command Reference

### Makefile Commands

```bash
make          # Generate certs, build, and start
make up       # Same as above
make down     # Stop and remove containers
make stop     # Stop containers (keep them)
make start    # Start stopped containers
make status   # Show container status
make logs     # Follow all logs
make certs    # Generate SSL certificates
make clean    # Remove containers and cache
make fclean   # Full cleanup (data + certs)
make re       # Rebuild from scratch
make help     # Show help message
```

### Docker Compose

```bash
# Build images
docker compose -f srcs/docker-compose.yml build

# Start services
docker compose -f srcs/docker-compose.yml up -d

# Stop services
docker compose -f srcs/docker-compose.yml stop

# Remove services
docker compose -f srcs/docker-compose.yml down

# View logs
docker compose -f srcs/docker-compose.yml logs -f

# Execute command in service
docker compose -f srcs/docker-compose.yml exec mariadb bash
```

### Docker

```bash
# List containers
docker ps
docker ps -a                      # Include stopped

# Remove container
docker rm container_name

# Remove image
docker rmi image_name

# View images
docker images

# Cleanup
docker system prune -a

# Volume management
docker volume ls
docker volume rm volume_name
docker volume prune
```

### WP-CLI Commands

```bash
# Inside WordPress container
wp user list --allow-root
wp post list --allow-root
wp plugin list --allow-root
wp theme list --allow-root
wp db check --allow-root
```

## Performance Optimization

### Image Size Reduction

- Use `.dockerignore` to exclude unnecessary files
- Clean apt cache: `rm -rf /var/lib/apt/lists/*`
- Combine RUN commands to reduce layers
- Use multi-stage builds if needed

### Resource Limits

Add to docker-compose.yml:

```yaml
services:
  mariadb:
    deploy:
      resources:
        limits:
          cpus: '1.0'
          memory: 512M
```

## Security Checklist

- [x] No hardcoded passwords in Dockerfiles
- [x] `.env` file in `.gitignore`
- [x] SSL certificates properly secured (600 for private keys)
- [x] Certificates auto-generated by Makefile
- [x] MariaDB not exposed to host network
- [x] Regular user created (not just admin)
- [x] Container runs as non-root user where possible
- [ ] Security updates applied to base images (manual process)


LE:

change port:
# Update WordPress URLs in database
docker exec wordpress wp option update home 'https://ccraciun.42.fr:8443' --allow-root
docker exec wordpress wp option update siteurl 'https://ccraciun.42.fr:8443' --allow-root

# Restart containers
docker restart wordpress nginx

# Test
curl -k https://ccraciun.42.fr:8443
