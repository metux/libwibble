SUBDIRS = wibble

enrico-publish: clean
	rsync -Cavz -P -e ssh ./ people.debian.org:public_html/wibble
