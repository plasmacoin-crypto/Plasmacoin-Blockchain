//
// FILENAME: upnp.go | Plasmacoin Cryptocurrency
// DESCRIPTION:
// CREATED: 2022-08-10 @ 1:10 AM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

package netutils

import (
	"context"
	"errors"
	"fmt"
	"strings"

	ig2 "github.com/huin/goupnp/dcps/internetgateway2"
	"golang.org/x/sync/errgroup"
)

type RouterClient interface {
	AddPortMapping(
		NewRemoteHost string,
		NewExternalPort uint16,
		NewProtocol string,
		NewInternalPort uint16,
		NewInternalClient string,
		NewEnabled bool,
		NewPortMappingDescription string,
		NewLeaseDuration uint32,
	) (err error)

	GetExternalIPAddress() (
		NewExternalIPAddress string,
		err error,
	)
}

func OpenPort(serviceID, protocol string, port uint16, host string) error {
	ctx := context.Background()
	var err error

	if len(serviceID) == 0 {
		return errors.New("invalid service ID")
	}

	// Get the UPnP client from it's service ID
	client, err := getClientBySID(ctx, serviceID)
	if err != nil {
		_ = fmt.Errorf(err.Error())
		return err
	}

	fmt.Println("Adding mapping")
	// Add the port mapping
	err = client.AddPortMapping("", port, strings.ToUpper(protocol), port, host, true, "Plasmacoin Client", 900)
	if err != nil {
		fmt.Println("Error")
		_ = fmt.Errorf(err.Error())
		return err
	}

	return nil
}

func GetServiceIDs() []string {
	ctx := context.Background()
	ip1Clients, ip2Clients, ppp1Clients := getClients(ctx)

	serviceIDs := make([]string, 0, len(ip1Clients)+len(ip2Clients)+len(ppp1Clients))

	for _, client := range ip1Clients {
		serviceIDs = append(serviceIDs, client.Service.ServiceId)
	}

	for _, client := range ip2Clients {
		serviceIDs = append(serviceIDs, client.Service.ServiceId)
	}

	for _, client := range ppp1Clients {
		serviceIDs = append(serviceIDs, client.Service.ServiceId)
	}

	return serviceIDs
}

func getClients(ctx context.Context) ([]*ig2.WANIPConnection1, []*ig2.WANIPConnection2, []*ig2.WANPPPConnection1) {
	tasks, _ := errgroup.WithContext(ctx)

	// Request each type of client in parallel, and return what is found.
	var ip1Clients []*ig2.WANIPConnection1
	tasks.Go(func() error {
		var err error
		ip1Clients, _, err = ig2.NewWANIPConnection1Clients()
		return err
	})

	var ip2Clients []*ig2.WANIPConnection2
	tasks.Go(func() error {
		var err error
		ip2Clients, _, err = ig2.NewWANIPConnection2Clients()
		return err
	})

	var ppp1Clients []*ig2.WANPPPConnection1
	tasks.Go(func() error {
		var err error
		ppp1Clients, _, err = ig2.NewWANPPPConnection1Clients()
		return err
	})

	if err := tasks.Wait(); err != nil {
		return nil, nil, nil
	}

	return ip1Clients, ip2Clients, ppp1Clients
}

func getClientBySID(ctx context.Context, serviceID string) (RouterClient, error) {
	ip1Clients, ip2Clients, ppp1Clients := getClients(ctx)

	switch {
	case len(ip1Clients) >= 1:
		clients := make([]RouterClient, 0, len(ip2Clients))

		for _, client := range ip1Clients {
			clients = append(clients, client)
		}

		for i, client := range ip1Clients {
			if client.Service.ServiceId == serviceID {
				return clients[i], nil
			}
		}
	case len(ip2Clients) >= 1:
		clients := make([]RouterClient, 0, len(ip2Clients))

		for _, client := range ip2Clients {
			clients = append(clients, client)
		}

		for i, client := range ip2Clients {
			if client.Service.ServiceId == serviceID {
				return clients[i], nil
			}
		}
	case len(ppp1Clients) >= 1:
		clients := make([]RouterClient, 0, len(ppp1Clients))

		for _, client := range ppp1Clients {
			clients = append(clients, client)
		}

		for i, client := range ppp1Clients {
			if client.Service.ServiceId == serviceID {
				return clients[i], nil
			}
		}
	default:
		return nil, errors.New("no services found")
	}

	return nil, errors.New("no services found")
}
