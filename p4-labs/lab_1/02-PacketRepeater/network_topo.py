from p4utils.mininetlib.network_API import NetworkAPI

net = NetworkAPI()

# Network general options
net.setLogLevel('info')
net.setCompiler(p4rt=True)
net.execScript('python control_plane.py', reboot=True)

# Network definition
net.addP4RuntimeSwitch('s1')
net.setP4Source('s1', 'packet_repeater.p4')
net.addHost('h1')
net.addHost('h2')

# Assignment strategy
net.addLink('h1', 's1')
net.addLink('h2', 's1')

# Nodes general options
net.enablePcapDumpAll()
net.enableLogAll()
net.enableCli()
net.startNetwork()