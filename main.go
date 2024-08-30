package main

import (
	"Lunarisnia/sdl-pong/internal/inputs"

	"github.com/veandco/go-sdl2/sdl"
)

const (
	screenWidth  = 640
	screenHeight = 480
)

type App struct {
	Window   *sdl.Window
	Renderer *sdl.Renderer
}

func main() {
	if err := sdl.Init(sdl.INIT_EVERYTHING); err != nil {
		panic(err)
	}
	defer sdl.Quit()
	sdl.Quit()
	app := App{}

	var err error
	app.Window, err = sdl.CreateWindow("testis", sdl.WINDOWPOS_UNDEFINED, sdl.WINDOWPOS_UNDEFINED, screenWidth, screenHeight, sdl.WINDOW_SHOWN)
	if err != nil {
		panic(err)
	}
	defer app.Window.Destroy()

	app.Renderer, err = sdl.CreateRenderer(app.Window, -1, sdl.RENDERER_ACCELERATED)
	if err != nil {
		panic(err)
	}
	defer app.Renderer.Destroy()

	rect := sdl.Rect{X: -300, Y: 0, W: 100, H: 100}

	running := true
	for running {
		app.Renderer.SetDrawColor(0, 0, 0, 255)
		app.Renderer.Clear()

		app.Renderer.SetDrawColor(255, 255, 255, 255)
		app.Renderer.DrawRect(&rect)

		inputs.HandleInput(func() {
			running = false
		})

		app.Renderer.Present()
		sdl.Delay(33)

		rect.X += 10
		if rect.X == 740 {
			rect.X = -300
		}
	}
}
