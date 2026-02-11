cd ..\build\Debug\

start "" dkv_server.exe --host 127.0.0.1 --port 8080 --peer 127.0.0.1:8081 --peer 127.0.0.1:8082 --peer 127.0.0.1:8083
start "" dkv_server.exe --host 127.0.0.1 --port 8081
start "" dkv_server.exe --host 127.0.0.1 --port 8082
start "" dkv_server.exe --host 127.0.0.1 --port 8083