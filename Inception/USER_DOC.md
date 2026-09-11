# User Documentation

This document explains how end users and administrators can interact with the Inception project.

## What Services Are Provided

The infrastructure provides:

1. **WordPress Website** - Content management system accessible via HTTPS
2. **NGINX Web Server** - Secure reverse proxy with TLS encryption
3. **MariaDB Database** - Backend database for WordPress data

All services are containerized and work together to provide a complete web hosting solution.

## Starting and Stopping the Project

### Start All Services

```bash
# From project root directory
make
# or
make up
```

This command will:
1. **Automatically generate SSL certificates** (if they don't exist)
2. Create necessary data directories
3. Build Docker images if they don't exist
4. Start all containers in detached mode
5. Set up networking between containers

**Expected output:**
```
✓ SSL certificates generated
✓ Data directories created
Building and starting containers...
Creating network "inception" with driver "bridge"
Creating mariadb ... done
Creating wordpress ... done
Creating nginx ... done
✓ All services started!
Access your site at: https://corin.42.fr
```

### Stop All Services

```bash
# Stop containers but keep data
make down
```

This preserves all website content and database data in `~/data/`.

### Other Useful Commands

```bash
make stop    # Pause containers without removing them
make start   # Resume stopped containers
make status  # Check which containers are running
make logs    # View real-time logs from all services
make help    # Show all available commands
```

## Accessing the Website

### Main Website

1. **Open browser and navigate to:**
   ```
   https://corin.42.fr
   ```

2. **Accept SSL certificate warning:**
   - Click "Advanced" → "Accept Risk and Continue"
   - This warning appears because we use self-signed certificates
   - Generated automatically by the Makefile

3. **View your WordPress site!**

### Administration Panel

1. **Navigate to:**
   ```
   https://corin.42.fr/wp-admin
   ```

2. **Login credentials:**
   - Find in `srcs/.env` file:
     - Username: `WP_ADMIN_USER`
     - Password: `WP_ADMIN_PASSWORD`

3. **Manage content:**
   - Create posts and pages
   - Install themes and plugins
   - Manage users
   - Configure site settings

## Managing Credentials

### Location of Credentials

All credentials are stored in `srcs/.env`:

```bash
cat srcs/.env
```

### Available Credentials

1. **Database Root Password:**
   ```
   MYSQL_ROOT_PASSWORD=<your-password>
   ```

2. **WordPress Database User:**
   ```
   MYSQL_USER=wpuser
   MYSQL_PASSWORD=<database-password>
   ```

3. **WordPress Admin:**
   ```
   WP_ADMIN_USER=<admin-username>
   WP_ADMIN_PASSWORD=<admin-password>
   ```

4. **WordPress Regular User:**
   ```
   WP_USER=<username>
   WP_USER_PASSWORD=<password>
   ```

### Changing Passwords

**⚠️ Warning:** Changing passwords requires rebuilding containers.

1. **Edit `.env` file:**
   ```bash
   nano srcs/.env
   ```

2. **Update desired passwords**

3. **Rebuild infrastructure:**
   ```bash
   make fclean  # Remove all data and certificates
   make         # Rebuild from scratch with new passwords
   ```

4. **WordPress will reinstall with new credentials**

## SSL Certificates

### Automatic Generation

SSL certificates are **automatically generated** when you run `make` or `make up`.

**What happens:**
- Makefile checks if certificates exist
- If missing, generates new self-signed certificates
- Uses your domain name (corin.42.fr)
- Valid for 365 days

**Certificate location:**
```
srcs/requirements/nginx/tools/
├── nginx.crt  (certificate)
└── nginx.key  (private key)
```

### Regenerating Certificates

```bash
# Full clean (removes certificates)
make fclean

# Start again (generates new certificates)
make
```

Or manually:
```bash
# Remove old certificates
rm -f srcs/requirements/nginx/tools/nginx.crt
rm -f srcs/requirements/nginx/tools/nginx.key

# Generate new ones
make certs
```

## Checking Service Health

### Quick Status Check

```bash
make status
```

**Expected output:**
```
CONTAINER ID   IMAGE       STATUS         PORTS
abc123         nginx       Up 5 minutes   0.0.0.0:443->443/tcp
def456         wordpress   Up 5 minutes   9000/tcp
ghi789         mariadb     Up 5 minutes   3306/tcp
```

All three containers should show "Up".

### Detailed Health Checks

#### 1. Check NGINX

```bash
docker exec nginx nginx -t
```

**Expected output:**
```
nginx: configuration file /etc/nginx/nginx.conf syntax is ok
nginx: configuration file /etc/nginx/nginx.conf test is successful
```

#### 2. Check MariaDB

```bash
docker exec mariadb mysqladmin ping -p
```

Enter the `MYSQL_ROOT_PASSWORD` when prompted.

**Expected output:**
```
mysqld is alive
```

#### 3. Check WordPress

```bash
docker exec wordpress wp --info --allow-root
```

Shows PHP and WordPress version information.

#### 4. View Service Logs

```bash
# All services
make logs

# Individual service
docker logs nginx
docker logs wordpress
docker logs mariadb

# Follow logs in real-time
docker logs -f nginx
```

### Common Issues and Solutions

#### Website Not Loading

**Check containers are running:**
```bash
docker ps
```

**Restart services:**
```bash
make down
make up
```

#### "Connection Refused" Error

**Verify domain in hosts file:**
```bash
cat /etc/hosts | grep corin.42.fr
```

Should show:
```
127.0.0.1 corin.42.fr
```

If missing, add it:
```bash
echo "127.0.0.1 corin.42.fr" | sudo tee -a /etc/hosts
```

#### Database Connection Error

**Check MariaDB is running:**
```bash
docker logs mariadb | grep "ready for connections"
```

**Verify WordPress can reach database:**
```bash
docker exec wordpress mysqladmin ping -h mariadb -u wpuser -p
```

Enter `MYSQL_PASSWORD` when prompted.

#### SSL Certificate Errors

Self-signed certificates always show browser warnings. This is normal!

**Regenerate if needed:**
```bash
make fclean  # Removes certificates
make         # Generates fresh ones
```

#### Certificates Not Generated

**Manual generation:**
```bash
make certs
```

**Check if they exist:**
```bash
ls -la srcs/requirements/nginx/tools/
```

Should show `nginx.crt` and `nginx.key`.

## Data Persistence

### Where Data Is Stored

All persistent data is stored on the host machine:

```bash
ls -la ~/data/
```

**Contents:**
- `~/data/mariadb/` - Database files
- `~/data/wordpress/` - WordPress files, uploads, themes, plugins

### Backing Up Data

```bash
# Create backup directory
mkdir -p ~/backups/$(date +%Y%m%d)

# Backup MariaDB
sudo tar -czf ~/backups/$(date +%Y%m%d)/mariadb.tar.gz ~/data/mariadb/

# Backup WordPress
sudo tar -czf ~/backups/$(date +%Y%m%d)/wordpress.tar.gz ~/data/wordpress/

# Backup configuration
cp srcs/.env ~/backups/$(date +%Y%m%d)/.env

# Backup certificates (optional)
cp srcs/requirements/nginx/tools/nginx.* ~/backups/$(date +%Y%m%d)/
```

### Restoring Data

```bash
# Stop containers
make down

# Restore from backup (example from 20260118)
sudo tar -xzf ~/backups/20260118/mariadb.tar.gz -C ~/
sudo tar -xzf ~/backups/20260118/wordpress.tar.gz -C ~/

# Restore certificates (optional)
cp ~/backups/20260118/nginx.* srcs/requirements/nginx/tools/

# Start containers
make up
```

## Routine Maintenance

### Checking Disk Usage

```bash
# Check data directory sizes
du -sh ~/data/*

# Check Docker disk usage
docker system df
```

### Cleaning Up Old Docker Data

```bash
# Remove unused images and containers
make clean

# Full cleanup (⚠️ removes all data and certificates!)
make fclean
```

### Updating WordPress

From WordPress admin panel:
1. Go to Dashboard → Updates
2. Click "Update Now"
3. Plugins and themes update through admin panel

### Viewing Active Users

```bash
docker exec wordpress wp user list --allow-root
```

## Complete Command Reference

```bash
make          # Generate certs and start all services
make up       # Same as above
make down     # Stop and remove containers
make stop     # Stop containers without removing
make start    # Start stopped containers
make status   # Show container status
make logs     # View all logs in real-time
make certs    # Generate SSL certificates
make clean    # Remove containers and Docker cache
make fclean   # Full cleanup (data + certificates)
make re       # Rebuild everything from scratch
make help     # Show available commands
```

## Security Best Practices

1. **Change default passwords** in `.env` before deployment
2. **Regular backups** - schedule weekly backups
3. **Update WordPress** - keep core, themes, and plugins updated
4. **Monitor logs** - check for suspicious activity
5. **Use strong passwords** - minimum 12 characters with mixed case, numbers, symbols
6. **Limit admin access** - use regular user accounts for daily work
7. **Regenerate certificates** - before they expire (365 days)

## Getting Help

If you encounter issues:

1. **Check logs:** `make logs`
2. **Verify configuration:** `cat srcs/.env`
3. **Check service status:** `make status`
4. **Review documentation:** See `DEV_DOC.md` for technical details
5. **Restart services:** `make down && make up`
6. **Regenerate certificates:** `make fclean && make`
7. **Check certificate validity:** `openssl x509 -in srcs/requirements/nginx/tools/nginx.crt -noout -dates`

## Quick Troubleshooting Flowchart

```
Problem: Website not accessible
  ↓
1. Check: Are containers running?
   → docker ps
   ↓ YES
2. Check: Is domain in /etc/hosts?
   → cat /etc/hosts | grep corin.42.fr
   ↓ YES
3. Check: Do SSL certificates exist?
   → ls srcs/requirements/nginx/tools/
   ↓ YES
4. Check: Are logs showing errors?
   → make logs
   ↓
5. Try: Restart services
   → make down && make up
```