package main

import (
	"Lunarisnia/sdl-pong/internal/core"
	"Lunarisnia/sdl-pong/internal/graphics"
	"Lunarisnia/sdl-pong/internal/inputs"
	"github.com/veandco/go-sdl2/sdl"
)

func main() {
	app := &core.App{}
	app.InitSDL()
	defer sdl.Quit()
	defer app.Window.Destroy()
	defer app.Renderer.Destroy()

	running := true
	for running {
		graphics.PrepareScene(app)

		inputs.HandleInput(func() {
			running = false
		})

		graphics.PresentScene(app)

		sdl.Delay(16)
	}
}
