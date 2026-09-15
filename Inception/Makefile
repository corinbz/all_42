
# Variables
DOCKER_COMPOSE = docker compose -f srcs/docker-compose.yml
DATA_DIR = /home/ccraciun/data
CERT_DIR = srcs/requirements/nginx/tools
CERT_KEY = $(CERT_DIR)/nginx.key
CERT_CRT = $(CERT_DIR)/nginx.crt
DOMAIN = ccraciun.42.fr

# Colors for output
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m # No Color

.PHONY: all up down stop start status logs clean fclean re certs

# Default target
all: up

# Generate SSL certificates if they don't exist
certs:
	@if [ ! -f $(CERT_KEY) ] || [ ! -f $(CERT_CRT) ]; then \
		echo "$(YELLOW)Generating SSL certificates...$(NC)"; \
		mkdir -p $(CERT_DIR); \
		openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
			-keyout $(CERT_KEY) \
			-out $(CERT_CRT) \
			-subj "/C=NL/ST=North-Holland/L=Amsterdam/O=42Network/OU=42/CN=$(DOMAIN)" 2>/dev/null; \
		echo "$(GREEN)✓ SSL certificates generated$(NC)"; \
	else \
		echo "$(GREEN)✓ SSL certificates already exist$(NC)"; \
	fi

# Build and start containers
up: certs
	@echo "$(YELLOW)Creating data directories...$(NC)"
	@mkdir -p $(DATA_DIR)/mariadb
	@mkdir -p $(DATA_DIR)/wordpress
	@echo "$(GREEN)✓ Data directories created$(NC)"
	@echo "$(YELLOW)Building and starting containers...$(NC)"
	@$(DOCKER_COMPOSE) up -d --build
	@echo "$(GREEN)✓ All services started!$(NC)"
	@echo "$(YELLOW)Access your site at: https://$(DOMAIN)$(NC)"

# Stop and remove containers
down:
	@echo "$(YELLOW)Stopping containers...$(NC)"
	@$(DOCKER_COMPOSE) down
	@echo "$(GREEN)✓ Containers stopped$(NC)"

# Stop containers without removing
stop:
	@echo "$(YELLOW)Stopping containers...$(NC)"
	@$(DOCKER_COMPOSE) stop
	@echo "$(GREEN)✓ Containers stopped$(NC)"

# Start stopped containers
start:
	@echo "$(YELLOW)Starting containers...$(NC)"
	@$(DOCKER_COMPOSE) start
	@echo "$(GREEN)✓ Containers started$(NC)"

# Show container status
status:
	@$(DOCKER_COMPOSE) ps

# Follow logs from all containers
logs:
	@$(DOCKER_COMPOSE) logs -f

# Clean: stop containers and remove Docker resources
clean: down
	@echo "$(YELLOW)Cleaning Docker system...$(NC)"
	@docker system prune -af
	@echo "$(GREEN)✓ Docker system cleaned$(NC)"

# Full clean: remove everything including data and certificates
fclean: clean
	@echo "$(RED)Removing all data and certificates...$(NC)"
	@sudo rm -rf $(DATA_DIR)/mariadb
	@sudo rm -rf $(DATA_DIR)/wordpress
	@rm -f $(CERT_KEY) $(CERT_CRT)
	@docker volume rm srcs_mariadb_data srcs_wordpress_data 2>/dev/null || true
	@echo "$(GREEN)✓ Full cleanup complete$(NC)"

# Rebuild everything from scratch
re: fclean all

# Help target
help:
	@echo "$(GREEN)Inception Project - Available targets:$(NC)"
	@echo ""
	@echo "  $(YELLOW)make$(NC) or $(YELLOW)make all$(NC)  - Generate certs and start all services"
	@echo "  $(YELLOW)make up$(NC)         - Generate certs and start containers"
	@echo "  $(YELLOW)make down$(NC)       - Stop and remove containers"
	@echo "  $(YELLOW)make stop$(NC)       - Stop containers (keep them)"
	@echo "  $(YELLOW)make start$(NC)      - Start stopped containers"
	@echo "  $(YELLOW)make status$(NC)     - Show container status"
	@echo "  $(YELLOW)make logs$(NC)       - Follow container logs"
	@echo "  $(YELLOW)make certs$(NC)      - Generate SSL certificates"
	@echo "  $(YELLOW)make clean$(NC)      - Remove containers and Docker cache"
	@echo "  $(YELLOW)make fclean$(NC)     - Full cleanup (removes data and certs)"
	@echo "  $(YELLOW)make re$(NC)         - Rebuild everything from scratch"
	@echo "  $(YELLOW)make help$(NC)       - Show this help message"
	@echo ""