#!/bin/sh
sudo chmod +x knn
./knn help
./knn -tr PATH/RAMBP_train.txt  -ts  PATH/RAMBP_test.txt  -k 1
