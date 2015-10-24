FROM debian:jessie

ENV LANG C.UTF-8

# add our user and group first to make sure their IDs get assigned consistently.
RUN groupadd -r nginx && useradd -r -g nginx nginx

RUN apt-get update && apt-get install -y --no-install-recommends \
	libexpat1 \
    && rm -rf /var/lib/apt/lists/*

ENV NGINX_VERSION   nginx-1.8.0
ENV OPENSSL_VERSION openssl-1.0.2d
ENV PCRE_VERSION    pcre-8.37
ENV ZLIB_VERSION    zlib-1.2.8

RUN set -x \
    && buildDeps='ca-certificates libexpat1-dev libc6-dev dpkg-dev curl make gcc git g++' \
    && apt-get update && apt-get install -y $buildDeps --no-install-recommends \
    && rm -rf /var/lib/apt/lists/* \
    && mkdir -p /usr/scr/nginx/nginx /usr/src/nginx/openssl /usr/src/nginx/pcre /usr/src/nginx/zlib \
       /usr/src/nginx/nginx-dav-ext-module /usr/src/nginx/nginx-upstream-fair /usr/src/nginx/ngx_http_substitutions_filter_module /usr/src/nginx/ngx_http_google_filter_module \
    && curl -SL "http://nginx.org/download/$NGINX_VERSION.tar.gz" -o nginx.tar.gz \
    && curl -SL "https://openssl.org/source/$OPENSSL_VERSION.tar.gz" -o openssl.tar.gz \
    && curl -SL "ftp://ftp.csx.cam.ac.uk/pub/software/programming/pcre/$PCRE_VERSION.tar.bz2"  -o pcre.tar.bz2 \
    && curl -SL "http://zlib.net/$ZLIB_VERSION.tar.xz" -o zlib.tar.xz \
    && tar -xzC /usr/src/nginx/nginx --strip-components=1 -f nginx.tar.gz \
    && tar -xzC /usr/src/nginx/openssl --strip-components=1 -f openssl.tar.gz \
    && tar -xjC /usr/src/nginx/pcre --strip-components=1 -f pcre.tar.bz2 \
    && tar -xJC /usr/src/nginx/zlib --strip-components=1 -f zlib.tar.xz \
    && rm -rf nginx.tar.gz openssl.tar.gz pcre.tar.bz2 zlib.tar.xz \
    && git clone https://github.com/arut/nginx-dav-ext-module /usr/src/nginx/nginx-dav-ext-module \
    && git clone https://github.com/gnosek/nginx-upstream-fair /usr/src/nginx/nginx-upstream-fair \
    && git clone https://github.com/yaoweibin/ngx_http_substitutions_filter_module /usr/src/nginx/ngx_http_substitutions_filter_module \
    && git clone https://github.com/cuber/ngx_http_google_filter_module /usr/src/nginx/ngx_http_google_filter_module \
    && cd /usr/src/nginx/nginx \
    && ./configure \
       --prefix=/var/www \
       --sbin-path=/usr/sbin/nginx \
       --conf-path=/etc/nginx/nginx.conf \
       --error-log-path=/var/log/nginx/log/error.log \
       --http-log-path=/var/log/nginx/access.log \
       --pid-path=/var/run/nginx.pid \
       --lock-path=/var/run/nginx.lock \
       --http-client-body-temp-path=/var/cache/nginx/client_temp \
       --http-proxy-temp-path=/var/cache/nginx/proxy_temp \
       --http-fastcgi-temp-path=/var/cache/nginx/fastcgi_temp \
       --http-scgi-temp-path=/var/cache/nginx/scgi_temp \
       --http-uwsgi-temp-path=/var/cache/nginx/uwsgi_temp \
       --user=nginx \
       --group=nginx \
       --with-cc-opt='-g -O2 -fstack-protector-strong -Wformat -Werror=format-security -Wp,-D_FORTIFY_SOURCE=2' \
       --with-ld-opt='-Wl,-z,relro -Wl,--as-needed' \
       --with-file-aio \
       --with-http_addition_module \
       --with-http_auth_request_module \
       --with-http_dav_module \
       --with-http_flv_module \
       --with-http_mp4_module \
       --with-http_gunzip_module \
       --with-http_gzip_static_module \
       --with-http_random_index_module \
       --with-http_realip_module \
       --with-http_secure_link_module \
       --with-http_spdy_module \
       --with-http_ssl_module \
       --with-http_stub_status_module \
       --with-http_sub_module \
       --with-ipv6 \
       --with-mail \
       --with-mail_ssl_module  \
       --with-openssl=../openssl \
       --with-pcre=../pcre \
       --with-zlib=../zlib \
       --add-module=../nginx-dav-ext-module \
       --add-module=../nginx-upstream-fair \
       --add-module=../ngx_http_google_filter_module \
       --add-module=../ngx_http_substitutions_filter_module \
    && make -j$(nproc) \
    && make install \
    && cd / \
    && rm -rf /usr/src/nginx \
    && openssl dhparam -out /etc/ssl/certs/dhparam.pem 2048 \

&& apt-get purge -y --auto-remove $buildDeps

ADD nginx /etc/init.d/nginx
RUN cd /etc/init.d && chown root:root nginx && chmod +x nginx

RUN echo "\ndaemon off;" >> /etc/nginx/nginx.conf
VOLUME ["/var/www", "/etc/nginx/conf.d", "/var/log/nginx", "/var/cache/nginx"]

EXPOSE 80
EXPOSE 443

CMD ["nginx"]
