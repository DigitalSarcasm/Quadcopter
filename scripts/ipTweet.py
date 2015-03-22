#!/usr/bin/env python
import socket
import sys
import time
import datetime
from twython import Twython

ip = [(s.connect(('8.8.8.8', 80)), s.getsockname()[0], s.close()) for s in [socket.socket(socket.AF_INET, socket.SOCK_DGRAM)]][0][1]
ts = time.time()
dt = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S')
tweetStr = "My current IPs: " + ip + "  :  " + dt

# your twitter consumer and access information goes here
# note: these are garbage strings and won't work
apiKey = '4IcNlkfnAIuPiAKGnflBxJeAR'
apiSecret = 'ktWfcsvbBrMN5ZrUCJc3H68iDJxWYL7nyeGhv0zSDeBsosh1rp'
accessToken = '2730494874-IfA2yxwPR6fxhEkV4M8fCJvvHkyLkR69KWxJqIw'
accessTokenSecret = 'Z0xx7Sm7W2ezvwZbAim8Ui4oh9BJUvqFGMTGJP8Hr3QKf'

api = Twython(apiKey,apiSecret,accessToken,accessTokenSecret)

api.update_status(status=tweetStr)

print ('Tweeted: ' + tweetStr)
