package main

/*
typedef const char* cchar_t;

typedef struct {
	cchar_t error;
} Error;
*/
import "C"

import (
	"encoding/json"
	"errors"
	"io/ioutil"
	"net"
	"net/http"
	"time"
)

// Check if a port is open on a certain host
//
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
//
//export GetGlobalIP
func GetGlobalIP() (string, C.Error) {
	resp, err := http.Get("http://ip-api.com/json/") // make a GET request
	body, _ := ioutil.ReadAll(resp.Body)             // Get the response as JSON

	// Convert the JSON string to a map
	responseMap := make(map[string]string)
	json.Unmarshal(body, &responseMap)

	if err != nil || responseMap["status"] == "fail" {
		goError := errors.New("could not get user's global IP address: " + responseMap["message"])
		cError := C.Error{C.CString(goError.Error())}

		return "", cError
	}

	defer resp.Body.Close()
	return responseMap["query"], C.Error{nil}
}

func main() {}
