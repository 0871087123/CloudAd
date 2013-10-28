echo "$1" > data.pub
scp data.pub kent@kent.skyteacher.net:/home/kent/config/data.pub
rm -rf data.pub
