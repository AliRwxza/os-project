clean:
	rm doc/main.aux doc/main.log doc/main.out doc/main.synctex.gz
docker:
	@docker run -it -v ./xv6:/src docker.arvancloud.ir/mmalekinejad/xv6 "/src/run"
