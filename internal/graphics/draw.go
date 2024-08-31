package graphics

import "Lunarisnia/sdl-pong/internal/core"

func PrepareScene(app *core.App) {
	app.Renderer.SetDrawColor(96, 128, 255, 255)
	app.Renderer.Clear()
}

func PresentScene(app *core.App) {
	app.Renderer.Present()
}
