docker build -t intravisor/cheri-sdk . 
docker login
docker push intravisor/cheri-sdk:latest
