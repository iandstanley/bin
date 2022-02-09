sudo rm /var/run/wpa_supplicant/wlan0
sudo wpa_supplicant -i wlan0 -c /etc/wpa_supplicant.conf &
sleep 5
ifconfig wlan0
