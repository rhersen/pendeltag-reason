install:	pull /opt/nginx/secure/reason/index.html

pull:
	git pull

build/index.html:	src/app.re
	npm run build

/opt/nginx/secure/reason/index.html:	build/index.html
	rm -R /opt/nginx/secure/reason
	mv build /opt/nginx/secure/reason
