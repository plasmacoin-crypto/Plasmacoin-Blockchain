package main

import (
	"fmt"
	"log"
	"net"
	"os"
	"sync"

	"github.com/plasmacoin-crypto/Plasmacoin-Blockchain/tcpnet"
	"github.com/plasmacoin-crypto/Plasmacoin-Blockchain/util"
)

var wg sync.WaitGroup

func main() {
	file := util.GzipCompress("/home/rmsmith/file.txt")

	file = util.GzipDecompress(file)
	defer file.Close()

	if c, err := os.ReadFile(file.Name()); err == nil {
		fmt.Println(string(c))
	} else {
		log.Fatal(err)
	}

	ch := make(chan net.Listener)

	wg.Add(3)

	go func(ch chan<- net.Listener) {
		l, err := tcpnet.Listen("tcp", "192.168.1.6", "8080")

		if err != nil {
			log.Fatal(err)
		}

		ch <- l
		wg.Done()
	}(ch)

	listener := <-ch

	fmt.Println(util.PortIsOpen("192.168.1.6", "67"))

	ip, err := util.GetGlobalIP()

	if err != nil {
		log.Fatal(err)
	}

	fmt.Println(ip)

	go tcpnet.Dial("tcp", "192.168.1.6", "8080", "Hello, World!")
	go tcpnet.Accept(listener)

	go func() {
		for {
			tcpnet.Dial("udp", "172.18.255.255", "8080", "Broadcasting...")
		}
	}()

	wg.Wait()
}
