.PHONY: permissions

permissions:
	mkdir -p dir
	echo "Hello, world!" > dir/file.txt
	# Grant all permissions on file.txt.
	chmod 777 dir/file.txt
	# Add read permissions (view entries) and remove execute permissions (access entries) on dir.
	chmod +r dir
	chmod -x dir
	# This should work
	ls dir
	# This should fail
	cat dir/file.txt || true
	# Remove read permissions (view entries) and add execute permissions (access entries) on dir.
	chmod -r dir
	chmod +x dir
	# This shouldn fail
	ls dir || true
	# This should  work
	cat dir/file.txt
	# Of course, the permissions on file.txt also matter when accessing it.
	chmod +rx dir
	chmod 000 dir/file.txt
	# We can see it, but we can't read from it, write to it, or execute it.
	ls dir
	cat dir/file.txt || true
	echo "foo" > dir/file.txt || true
	# However, deleting it has to do with the permissions on dir (because it is its content we're changing).
	# This should fail
	chmod -w dir
	rm -f dir/file.txt || true
	# This should work (even though we have no permissions to do anything with file.txt).
	chmod +w dir
	rm -f dir/file.txt || true

# NOTE: when a command returns a non-zero exit code (like when ls/cat fail), make stops.
# || is bash for "if the left command failed, do the right command", and true is a dummy
# command that always returns zero, so adding "|| true" makes the entire command succeed
# and keep make happy.

.PHONY: filesystem

filesystem:
	# Copy 1048576 (1MB) zeroes into blob.
	head -c 1048576 /dev/zero > blob
	# Format blob so it resembles an EXT4 filesystem.
	mkfs.ext4 blob
	# Make sure blob does not contain the string "Hello, world!"
	grep "Hello, world!" blob || true
	# Create a directory unto which we'll mount that filesystem.
	mkdir -p mp
	# See that it's empty?
	ls -l mp
	# Mount blob unto mp, so it becomes the entry to its root directory.
	sudo mount blob mp
	sudo chown -R $(USER) mp
	# Suddenly, it's not empty! (EXT4 has a lost+found directory by default).
	ls -l mp
	# Let's add a file to our filesystem.
	echo "Hello, world!" > mp/file.txt
	ls -l mp
	# Now let's unmount it.
	sudo umount mp
	# Our file is gone!
	ls -l mp
	# Or rather, it is in a filesystem that is no longer mounted, and thus no longer accessible via the mp directory.
	grep "Hello, world!" blob
	hd blob | grep "Hello, world!"
