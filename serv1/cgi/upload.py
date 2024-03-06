#!/usr/bin/python3
import cgi
import sys
import os

form = cgi.FieldStorage()
root = sys.argv[1]


fileitem = form["file"]


if fileitem.filename:
	fn = os.path.basename(fileitem.filename)
	open(root + "/uploads/" + fn, "wb").write(fileitem.file.read())
	message = "The file " + fn + " was uploaded successfully"
else:
	message = "No file was uploaded"


print("Content-Type: text/html\n")
print("<html>")
print("<body>")
print("<h1 style=\"color:whitesmoke;\">Upload page</h1>")
print("<p style=\"color:whitesmoke;\">" + message)
print("<h3 style=\"color:whitesmoke;\" >Come back to <a href=\"../upload.html\" style=\"color:red;\"> Upload </a></h3>")
print("</p>")
print("<body style=\"background-color:#363535;\">")
print("</body>")
print("</html>")