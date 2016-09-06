import urllib.request

with urllib.request.urlopen('https://www.google.com') as req:
	print(req.read())
