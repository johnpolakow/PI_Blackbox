sudo apt-get install -y html-xml-utils
#wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.62.tar.gz;
cd bcm2835
tar zxvf bcm2835-1.62.tar.gz
cd bcm2835-1.62
./configure
make
sudo make check
sudo make install
