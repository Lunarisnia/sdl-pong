package inputs

import (
	"fmt"

	"github.com/veandco/go-sdl2/sdl"
)

func HandleInput(quit func()) {
	for event := sdl.PollEvent(); event != nil; event = sdl.PollEvent() {
		switch event.(type) {
		case *sdl.QuitEvent:
			fmt.Println("Quit")
			quit()
		default:
			break
		}
	}
}
