#!/usr/local/bin/python3
import os

# Get the request method from the environment variables
method = os.environ.get('REQUEST_METHOD', '')

# Start generating the HTML page
page = "<h1>"

# Check the request method
if method == 'GET':
    page += "This is a GET request."
elif method == 'POST':
    page += "This is a POST request."
else:
    page += "Unsupported request method."

# Close the HTML tags
page += "</h1>"

# Calculate the Content-Length
content_length = len(page.encode('utf-8'))

# Print the headers
print("200 Ok HTTP/1.1", end='\r\n')
print("Content-Type: text/html", end='\r\n')
print(f"Content-Length: {content_length}", end='')
print(end='\r\n\r\n')

# Print the HTML page
print(page, end='\r\n')