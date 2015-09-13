#Nginx
======

```
参考书籍: 《精通Nginx》
          ISBN: 978-7-115-38141-5
```

####编译选项
```
> ./configure \
> --prefix=/etc/nginx \
> --sbin-path=/usr/sbin/nginx \
> --conf-path=/etc/nginx/nginx.conf \
> --error-log-path=/home/nginx/log/error.log \
> --http-log-path=/home/nginx/log/access.log \
> --pid-path=/var/run/nginx.pid \
> --lock-path=/var/run/nginx.lock \
> --http-client-body-temp-path=/var/cache/nginx/client_temp \
> --http-proxy-temp-path=/var/cache/nginx/proxy_temp \
> --http-fastcgi-temp-path=/var/cache/nginx/fastcgi_temp \
> --http-scgi-temp-path=/var/cache/nginx/scgi_temp \
> --http-uwsgi-temp-path=/var/cache/nginx/uwsgi_temp \
> --user=nginx \
> --group=nginx \
> --with-cc-opt='-g -O2 -fstack-protector-strong -Wformat -Werror=format-security -Wp,-D_FORTIFY_SOURCE=2' \
> --with-ld-opt='-Wl,-z,relro -Wl,--as-needed' \
> --with-file-aio \
> --with-http_addition_module \
> --with-http_auth_request_module \
> --with-http_dav_module \
> --with-http_flv_module \
> --with-http_mp4_module \
> --with-http_gunzip_module \
> --with-http_gzip_static_module \
> --with-http_random_index_module \
> --with-http_realip_module \
> --with-http_secure_link_module \
> --with-http_spdy_module \
> --with-http_ssl_module \
> --with-http_stub_status_module \
> --with-http_sub_module \
> --with-ipv6 \
> --with-mail \
> --with-mail_ssl_module  \
> --with-openssl=../openssl-1.0.2d \
> --with-pcre=../pcre-8.37 \
> --with-zlib=../zlib-1.2.8 \
> --add-module=../nginx-dav-ext-module \
> --add-module=../nginx-upstream-fair \
> --add-module=../ngx_http_google_filter_module \
> --add-module=../ngx_http_substitutions_filter_module

注:
包含debian 32位安装nginx后所有的编译选项(#nginx -V查看)。
改变了一些设置:
--error-log-path
--http-log-path
额外添加了一些module:
ngx_http_google_filter_module
ngx_http_substitutions_filter_module
用于开启google镜像.
(其它添加的model,忘了是不是原有的...)
          相关模块下载可在github上搜索到
编译过程遇到任何问题请Google
```

####配置
```
ssl身份验证、强制ssl加密连接(通过80端口重定向)
多个server_name匹配
反向代理、反向代理性能调优:缓冲、缓存、压缩
mail服务器(待配置)
```
