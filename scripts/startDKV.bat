cd ..\build\Debug\


rem start "" dkv_server.exe --host 127.0.0.1 --port 8080 --node node0 --peer node1@127.0.0.1:8081
rem start "" dkv_server.exe --host 127.0.0.1 --port 8081 --node node1 --peer node0@127.0.0.1:8080

rem start "" dkv_server.exe --host 127.0.0.1 --port 8080 --node node0 --peer node1@127.0.0.1:8081 --peer node2@127.0.0.1:8082
rem start "" dkv_server.exe --host 127.0.0.1 --port 8081 --node node1
rem start "" dkv_server.exe --host 127.0.0.1 --port 8082 --node node2
rem start "" dkv_server.exe --host 127.0.0.1 --port 8083 --node node3

start "" dkv_server.exe --host 127.0.0.1 --port 8080 --node node0 --peer node1@127.0.0.1:8081 --peer node2@127.0.0.1:8082 --peer node3@127.0.0.1:8083
start "" dkv_server.exe --host 127.0.0.1 --port 8081 --node node1 --peer node0@127.0.0.1:8080 --peer node2@127.0.0.1:8082 --peer node3@127.0.0.1:8083
start "" dkv_server.exe --host 127.0.0.1 --port 8082 --node node2 --peer node0@127.0.0.1:8080 --peer node1@127.0.0.1:8081 --peer node3@127.0.0.1:8083
start "" dkv_server.exe --host 127.0.0.1 --port 8083 --node node3 --peer node0@127.0.0.1:8080 --peer node1@127.0.0.1:8081 --peer node2@127.0.0.1:8082