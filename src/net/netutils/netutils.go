//
// FILENAME: netlisten.go | Plasmacoin Cryptocurrency
// DESCRIPTION: Listen for TCP/UDP connections
// CREATED: 2021-09-06 @ 8:10 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

package netutils

import (
	"encoding/json"
	"errors"
	"fmt"
	"io/ioutil"
	"net"
	"net/http"
	"os/exec"
	"runtime"
	"strconv"
	"time"
)

// Check for errors
func Check(err error, line int) {
	if err != nil {
		var _ error = fmt.Errorf(err.Error(), " on line ", strconv.Itoa(line))
	}
}

// Check if a port is open on a certain host
//export PortIsOpen
func PortIsOpen(host, port string) bool {
	addr := net.JoinHostPort(host, port)

	if conn, err := net.DialTimeout("tcp", addr, time.Second); conn != nil && err == nil {
		defer conn.Close()
		return true
	}

	return false
}

// Get the user's global IP address by making a call to http://ip-api.com/json/.
//export GetGlobalIP
func GetGlobalIP() string {
	resp, err := http.Get("http://ip-api.com/json/") // make a GET request
	body, _ := ioutil.ReadAll(resp.Body)             // Get the response as JSON

	// Convert the JSON string to a map
	responseMap := make(map[string]string)
	json.Unmarshal(body, &responseMap)

	if err != nil || responseMap["status"] == "fail" {
		panic(errors.New("could not get user's global IP address: " + responseMap["message"]))
	}

	defer resp.Body.Close()
	return responseMap["query"]
}

func Ping(host string) bool {
	var cmd *exec.Cmd

	switch runtime.GOOS {
	case "linux", "darwin":
		cmd = exec.Command("ping", host, "-q", "-c 1")
	case "windows":
		cmd = exec.Command("ping", host, "/n 1", "> nul")
	}

	if err := cmd.Run(); err == nil {
		return true
	} else {
		return false
	}
}
