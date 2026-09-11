FROM debian:bullseye

RUN apt-get update && apt-get install -y \
	nginx \
	&& rm -rf /var/lib/apt/lists/*

# Create SSL directory
RUN mkdir -p /etc/nginx/ssl

# Copy config and SSL certificates
COPY conf/nginx.conf /etc/nginx/nginx.conf
COPY tools/nginx.crt /etc/nginx/ssl/nginx.crt
COPY tools/nginx.key /etc/nginx/ssl/nginx.key

# Set permissions
RUN chmod 644 /etc/nginx/ssl/nginx.crt && \
    chmod 600 /etc/nginx/ssl/nginx.key

EXPOSE 443	

CMD ["nginx", "-g", "daemon off;"]	
