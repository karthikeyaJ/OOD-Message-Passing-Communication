:run
start .\Debug\Peer1.exe server 9083 9084 abc
start .\Debug\Peer2.exe client 9083 9084 img2.jpg
start .\Debug\Peer2.exe client 9083 9085 html.txt