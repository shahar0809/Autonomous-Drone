#!/bin/bash


# Install virtual environment
sudo pip2 install virtualenv virtualenvwrapper
sudo pip3 install virtualenv virtualenvwrapper
echo "# Virtual Environment Wrapper"  >> ~/.bashrc
echo "source /usr/local/bin/virtualenvwrapper.sh" >> ~/.bashrc
source ~/.bashrc

############ For Python 2 ############
# create virtual environment
mkvirtualenv facecourse-py2 -p python2
workon facecourse-py2

# now install python libraries within this virtual environment
pip install numpy scipy matplotlib scikit-image scikit-learn ipython

# quit virtual environment
deactivate
######################################

############ For Python 3 ############
# create virtual environment
mkvirtualenv facecourse-py3 -p python3
workon facecourse-py3

# now install python libraries within this virtual environment
pip install numpy scipy matplotlib scikit-image scikit-learn ipython

# quit virtual environment
deactivate
######################################