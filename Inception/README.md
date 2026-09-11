# Inception

![42](https://img.shields.io/badge/42-project-000000?style=flat-square&logo=42&logoColor=white)
![Docker](https://img.shields.io/badge/tooling-Docker%20Compose-blue?style=flat-square)
![Status](https://img.shields.io/badge/status-completed-brightgreen?style=flat-square)

*corin created this project as part of the 42 curriculum.*

## Description

Inception is a system administration project that sets up a small infrastructure with Docker. It runs a multi-container application made of:

- NGINX web server with TLS encryption
- WordPress content management system with PHP-FPM
- MariaDB database server

All services run in isolated Docker containers, connected via a custom network, with persistent data storage.

## Architecture overview

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

1. Clone the repository:
```bash
git clone <repository-url>
cd inception
```

2. Configure the domain:
```bash
echo "127.0.0.1 corin.42.fr" | sudo tee -a /etc/hosts
```

3. Set up environment variables:
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

4. Build and launch:
```bash
make
```

The Makefile then:
- Generate SSL certificates
- Create data directories
- Build Docker images
- Start all containers

5. Access the site:
- Open browser: `https://corin.42.fr`
- Admin panel: `https://corin.42.fr/wp-admin`

### Management commands

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

### Official documentation
- [Docker Documentation](https://docs.docker.com/)
- [Docker Compose Reference](https://docs.docker.com/compose/)
- [NGINX Documentation](https://nginx.org/en/docs/)
- [WordPress CLI](https://wp-cli.org/)
- [MariaDB Documentation](https://mariadb.org/documentation/)

### Tutorials
- [Docker Networking](https://docs.docker.com/network/)
- [Docker Volumes](https://docs.docker.com/storage/volumes/)
- [PHP-FPM Configuration](https://www.php.net/manual/en/install.fpm.php)

### AI usage

This project used AI tools to optimize Dockerfiles (multi-stage builds,
smaller images), debug NGINX/PHP-FPM/MariaDB configuration issues, write
the initialization and setup bash scripts, structure this documentation,
and write the Makefile's build and certificate-generation targets.

I reviewed, tested, and adjusted every AI-generated piece to meet the
project's requirements.

## Project design choices

### Virtual machines vs Docker

Virtual machines virtualize the whole OS, kernel included. That gives
complete isolation, but they take minutes to start and use more
resources. Docker containers share the host kernel instead, so they
start in seconds and use fewer resources, which suits a multi-service
setup like this one. This project uses Docker.

### Secrets vs environment variables

Environment variables (`.env`) hold non-sensitive configuration like the
domain name and database names. They're easy to read and modify, but can
end up committed to git by accident. Secrets give encrypted storage for
passwords and keys and are the better choice for production (Docker
Swarm supports them natively). This project uses `.env` for simplicity,
protected by `.gitignore`.

### Docker network vs host network

Host network mode gives a container the host's own network stack, so
there is no isolation and ports can conflict. A Docker network isolates
each container in its own namespace, resolves other containers by name
through DNS, and exposes only the ports a container opens. This project
uses a Docker network.

### Docker volumes vs bind mounts

Bind mounts map a host path directly into the container. That is simple,
but it ties the setup to host-specific paths. Docker manages volumes
itself, so they perform better, move between systems more easily, and
are simpler to back up. This project uses volumes, with bind mounts for
the specific host paths that need them.

## Key features

- TLS 1.2/1.3 for HTTPS
- The Makefile generates the SSL certificates
- Data persists across container restarts
- Each service runs in its own container
- Containers restart on crash
- Credentials come from environment variables, not the images
- A custom network connects the services
- Alpine/Debian base images keep the images small
- `make` deploys everything in one command

## Security considerations

- The SSL certificates are self-signed (for production, use Let's Encrypt)
- Passwords live in `.env`, which git ignores
- Only containers on the Docker network can reach MariaDB
- Only the NGINX reverse proxy can reach WordPress
- A regular (non-admin) user account exists for day-to-day use

## File structure

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