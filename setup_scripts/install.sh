#!/bin/bash

echo -e "installing command scsd..."
cd ../
make
sudo mv ./scsd /usr/bin/
make fclean
echo -e "All done"