$bootstrap = <<BOOTSTRAP
export DEBIAN_FRONTEND=noninteractive
apt-get update
apt-get -y install build-essential
apt-get -y install cmake
apt-get -y install valgrind
apt-get -y install lcov
apt-get -y install python3-pip
pip3 install pexpect
BOOTSTRAP

Vagrant.configure("2") do |config|
  config.vm.box = "ubuntu/xenial32"
  
  # setup the VM
  config.vm.provision "shell", inline: $bootstrap
  
end

