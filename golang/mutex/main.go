package main

import (
	"fmt"
	"sync"
	"time"

	"github.com/pkg/errors"
)

type wrappedTime struct {
	mu          sync.Mutex
	initialized bool
	time        time.Time
}

func (w *wrappedTime) Initialize(t time.Time) error {
	w.mu.Lock()
	defer w.mu.Unlock()
	if w.initialized {
		return errors.New("already initialized")
	}
	time.Sleep(time.Second * 1)
	w.initialized = true
	w.time = t
	return nil
}

func (w *wrappedTime) Get() (time.Time, error) {
	if !w.initialized {
		return time.Time{}, errors.New("wrapped time is not initialized.")
	}
	time.Sleep(time.Second * 1)
	return w.time, nil
}

var wt = wrappedTime{}

func initialize(wg *sync.WaitGroup) {
	defer wg.Done()
	err := wt.Initialize(time.Now())
	if err != nil {
		fmt.Println(err)
		return
	}
	w, err := wt.Get()
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println(w)
}

func main() {
	wg := sync.WaitGroup{}
	for i := 0; i < 100; i++ {
		wg.Add(1)
		initialize(&wg)
	}
	wg.Wait()
}
