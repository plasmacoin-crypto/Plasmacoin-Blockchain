#
# FILENAME: getglobip.py | Plasmacoin Cryptocurrency
# DESCRIPTION: Get the user's global IP address and save it to a file
# CREATED: 2021-02-14 @ 5:38 PM
# COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
#

import os, urllib.request, subprocess

global_ip = urllib.request.urlopen("https://ident.me").read().decode("utf-8") # Get the global IP address

# This will write to a write-protected file, so this script
# must be called with root permissions
if os.environ.get("GLOBAL_IP") != global_ip:
	with open("/etc/environment", "r+") as env:
		contents = env.readlines()

		# Find the line that the environment variable is defined on and
		# update the IP address at that location in the file.
		index = contents.index("GLOBAL_IP", 0, len(contents))
		contents[index] = f"GLOBAL_IP=\"{global_ip}\""

		env.writelines(contents) # Update the file itself

subprocess.call("source /etc/environment", shell=True) # Update the environment
