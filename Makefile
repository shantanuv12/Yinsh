all:
	python server.py 10000 -n 5 -NC 2 -TL 150 -LOG server.log&
	python client.py 0.0.0.0 10000 RandomPlayer.py -mode GUI&
	python client.py 0.0.0.0 10000 run.sh

server:
	python server.py 10000 -n 5 -NC 2 -TL 150 -LOG server.log

random:
	python client.py 0.0.0.0 10000 RandomPlayer.py -mode GUI

compile:
	g++ bot.cpp -o bot
bot:
	python client.py 0.0.0.0 10000 run.sh

clean:
	find . -name 'bot' -delete
