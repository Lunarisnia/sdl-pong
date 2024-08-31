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

	playerSprite, err := graphics.LoadTexture(app.Renderer, "assets/player.png")
	if err != nil {
		panic(err)
	}
	_, _, width, height, err := playerSprite.Query()
	if err != nil {
		panic(err)
	}

	player := dsu.Entity{
		Position: dsu.Vector2i{
			X: core.ScreenWidth/2 - width*10.0/2,
			Y: core.ScreenHeight/2 - height*10.0/2,
		},
		Texture: playerSprite,
	}

	running := true
	for running {
		graphics.PrepareScene(app.Renderer)

		graphics.Blit(app.Renderer, player.Texture, player.Position, 10.0)

		inputs.HandleInput(func() {
			running = false
		})

		graphics.PresentScene(app.Renderer)

		sdl.Delay(16)

		// player.Position = player.Position.Add(dsu.Vector2i{X: 1, Y: 1})
		// player.Position.X %= 500
		// player.Position.Y %= 500
	}
}
