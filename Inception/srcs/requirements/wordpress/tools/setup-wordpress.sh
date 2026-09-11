#!/bin/bash
set -e

cd /var/www/html

# Wait for MariaDB to be ready
echo "Waiting for MariaDB to be ready..."
until mysqladmin ping -h mariadb -u${MYSQL_USER} -p${MYSQL_PASSWORD} --silent; do
    echo "MariaDB is unavailable - sleeping"
    sleep 2
done
echo "MariaDB is up!"

# Download WordPress if not already present
if [ ! -f wp-config.php ]; then
    echo "Downloading WordPress..."
    wp core download --allow-root

    echo "Creating wp-config.php..."
    wp config create \
        --dbname=${MYSQL_DATABASE} \
        --dbuser=${MYSQL_USER} \
        --dbpass=${MYSQL_PASSWORD} \
        --dbhost=mariadb:3306 \
        --allow-root

    echo "Installing WordPress..."
    wp core install \
        --url=${WP_URL} \
        --title="${WP_TITLE}" \
        --admin_user=${WP_ADMIN_USER} \
        --admin_password=${WP_ADMIN_PASSWORD} \
        --admin_email=${WP_ADMIN_EMAIL} \
        --skip-email \
        --allow-root

    echo "Creating additional user..."
    wp user create ${WP_USER} ${WP_USER_EMAIL} \
        --user_pass=${WP_USER_PASSWORD} \
        --role=author \
        --allow-root

    echo "WordPress setup complete!"
fi

# Ensure correct permissions
chown -R www-data:www-data /var/www/html

# Start PHP-FPM in foreground
echo "Starting PHP-FPM..."
mkdir -p /run/php
exec php-fpm7.4 -F
```

**Create `srcs/requirements/wordpress/.dockerignore`:**
```
.git
.gitignore