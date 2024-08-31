package main

import (
	"Lunarisnia/sdl-pong/internal/core"
	"Lunarisnia/sdl-pong/internal/dsu"
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

	player, err := graphics.LoadTexture(app.Renderer, "assets/player.png")
	if err != nil {
		panic(err)
	}

	playerPosition := dsu.Vector2i{
		X: 0,
		Y: 0,
	}

	running := true
	for running {
		graphics.PrepareScene(app.Renderer)

		graphics.Blit(app.Renderer, player, playerPosition)

		inputs.HandleInput(func() {
			running = false
		})

		graphics.PresentScene(app.Renderer)

		sdl.Delay(16)

		playerPosition = playerPosition.Add(dsu.Vector2i{X: 1, Y: 1})
		playerPosition.X %= 500
		playerPosition.Y %= 500
	}
}
