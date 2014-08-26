export LD_LIBRARY_PATH=/root/mjpeg_face_leaf_detection/mjpg-streamer

./mjpg_streamer -i "input_uvc.so -y -f 5 -r 640*480 -q 60" "output_http.so -p 8080 -w /var/www"
