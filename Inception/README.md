# Inception

*This project has been created as part of the 42 curriculum by corin.*

## Description

Inception is a system administration project that involves setting up a small infrastructure using Docker. The project creates a multi-container application consisting of:

- **NGINX** web server with TLS encryption
- **WordPress** content management system with PHP-FPM
- **MariaDB** database server

All services run in isolated Docker containers, connected via a custom network, with persistent data storage.

## Architecture Overview

```
┌─────────────────────────────────────────┐
│           Host Machine (VM)             │
│                                         │
│  ┌───────────────────────────────────┐ │
│  │   Docker Network: inception       │ │
│  │                                   │ │
│  │  ┌─────────┐    ┌──────────┐    │ │
│  │  │ NGINX   │───▶│WordPress │    │ │
│  │  │ :443    │    │ :9000    │    │ │
│  │  └─────────┘    └────┬─────┘    │ │
│  │                      │           │ │
│  │                      ▼           │ │
│  │                ┌──────────┐     │ │
│  │                │ MariaDB  │     │ │
│  │                │ :3306    │     │ │
│  │                └──────────┘     │ │
│  └───────────────────────────────────┘ │
│                                         │
│  Persistent Volumes:                    │
│  ~/data/wordpress                       │
│  ~/data/mariadb                         │
└─────────────────────────────────────────┘
```

## Instructions

### Prerequisites

- Debian-based virtual machine
- Docker and Docker Compose installed
- Minimum 2GB RAM, 10GB disk space

### Installation

1. **Clone the repository:**
```bash
git clone <repository-url>
cd inception
```

2. **Configure domain:**
```bash
echo "127.0.0.1 corin.42.fr" | sudo tee -a /etc/hosts
```

3. **Set up environment variables:**
```bash
# Create .env file with your credentials
nano srcs/.env
```

Add the following (replace passwords with strong ones):
```env
DOMAIN_NAME=corin.42.fr
MYSQL_ROOT_PASSWORD=your_strong_root_password
MYSQL_DATABASE=wordpress
MYSQL_USER=wpuser
MYSQL_PASSWORD=your_strong_user_password
WP_ADMIN_USER=siteowner
WP_ADMIN_PASSWORD=your_admin_password
WP_ADMIN_EMAIL=admin@example.com
WP_USER=blogwriter
WP_USER_EMAIL=user@example.com
WP_USER_PASSWORD=your_user_password
WP_TITLE=Inception Project
WP_URL=https://corin.42.fr
```

4. **Build and launch (SSL certificates generated automatically):**
```bash
make
```

The Makefile will automatically:
- Generate SSL certificates
- Create data directories
- Build Docker images
- Start all containers

5. **Access the site:**
- Open browser: `https://corin.42.fr`
- Admin panel: `https://corin.42.fr/wp-admin`

### Management Commands

```bash
make          # Generate certs and start all services
make up       # Same as above
make down     # Stop and remove containers
make stop     # Stop containers without removing
make start    # Start stopped containers
make status   # Show container status
make logs     # View all logs in real-time
make certs    # Generate SSL certificates (if needed)
make clean    # Remove containers and Docker cache
make fclean   # Full cleanup (removes data and certificates)
make re       # Rebuild everything from scratch
make help     # Show available commands
```

## Resources

### Official Documentation
- [Docker Documentation](https://docs.docker.com/)
- [Docker Compose Reference](https://docs.docker.com/compose/)
- [NGINX Documentation](https://nginx.org/en/docs/)
- [WordPress CLI](https://wp-cli.org/)
- [MariaDB Documentation](https://mariadb.org/documentation/)

### Tutorials
- [Docker Networking](https://docs.docker.com/network/)
- [Docker Volumes](https://docs.docker.com/storage/volumes/)
- [PHP-FPM Configuration](https://www.php.net/manual/en/install.fpm.php)

### AI Usage

AI tools were used in this project for:
- **Dockerfile optimization**: Generating efficient multi-stage builds and reducing image sizes
- **Configuration debugging**: Troubleshooting NGINX, PHP-FPM, and MariaDB configuration issues
- **Script generation**: Creating initialization and setup bash scripts
- **Documentation**: Structuring and formatting technical documentation
- **Makefile automation**: Implementing build automation and certificate generation

All AI-generated content was thoroughly reviewed, tested, and modified to ensure correctness and compliance with project requirements.

## Project Design Choices

### Virtual Machines vs Docker

**Virtual Machines:**
- Full OS virtualization with kernel
- Higher resource overhead
- Complete isolation
- Minutes to start

**Docker (chosen):**
- Container-based virtualization
- Shares host kernel
- Lightweight and fast (seconds to start)
- Better resource efficiency
- Ideal for microservices architecture

### Secrets vs Environment Variables

**Environment Variables (.env):**
- Used for non-sensitive configuration (domain, database names)
- Easily readable and modifiable
- Can be accidentally committed to git

**Secrets (recommended for production):**
- Encrypted storage for passwords and keys
- Better security practices
- Docker secrets support in Swarm mode
- This project uses `.env` for simplicity, with `.gitignore` protection

### Docker Network vs Host Network

**Host Network:**
- Container uses host's network stack
- No isolation
- Port conflicts possible

**Docker Network (chosen):**
- Isolated network namespace
- DNS-based service discovery (containers communicate by name)
- Network segmentation and security
- Containers can only expose specific ports

### Docker Volumes vs Bind Mounts

**Bind Mounts:**
- Direct host path mounting
- Host-dependent paths
- Less portable

**Docker Volumes (chosen):**
- Managed by Docker
- Better performance
- Portable across systems
- Easier backup and migration
- Used with bind mount options for specific host paths

## Key Features

✅ **TLS 1.2/1.3 encryption** for secure HTTPS connections  
✅ **Automatic SSL certificate generation** via Makefile  
✅ **Persistent data storage** survives container restarts  
✅ **Isolated services** in dedicated containers  
✅ **Automatic restart** on crash  
✅ **No hardcoded credentials** (environment variables)  
✅ **Custom network** for inter-service communication  
✅ **Alpine/Debian base images** for minimal attack surface  
✅ **One-command deployment** with `make`

## Security Considerations

- SSL certificates are self-signed (for production, use Let's Encrypt)
- Passwords stored in `.env` (excluded from git)
- MariaDB only accessible within Docker network
- WordPress accessible only through NGINX reverse proxy
- Regular user account created (admin-only access discouraged)

## File Structure

```
inception/
├── Makefile                      # Build automation with SSL generation
├── README.md
├── USER_DOC.md
├── DEV_DOC.md
├── .gitignore
└── srcs/
    ├── docker-compose.yml
    ├── .env                      # Your credentials (not in git)
    └── requirements/
        ├── mariadb/
        │   ├── Dockerfile
        │   ├── conf/50-server.cnf
        │   └── tools/init-db.sh
        ├── wordpress/
        │   ├── Dockerfile
        │   ├── conf/www.conf
        │   └── tools/setup-wordpress.sh
        └── nginx/
            ├── Dockerfile
            ├── conf/nginx.conf
            └── tools/
                ├── nginx.crt     # Auto-generated by Makefile
                └── nginx.key     # Auto-generated by Makefile
```

## Troubleshooting

See `USER_DOC.md` and `DEV_DOC.md` for detailed troubleshooting guides.

## License

This project is part of the 42 School curriculum.