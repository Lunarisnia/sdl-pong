package core

import "github.com/veandco/go-sdl2/sdl"

const (
	ScreenWidth  = 640
	ScreenHeight = 480
)

type App struct {
	Window   *sdl.Window
	Renderer *sdl.Renderer
}

func (a *App) InitSDL() {
	if err := sdl.Init(sdl.INIT_EVERYTHING); err != nil {
		panic(err)
	}

	var err error
	a.Window, err = sdl.CreateWindow(
		"main",
		sdl.WINDOWPOS_CENTERED,
		sdl.WINDOWPOS_CENTERED,
		ScreenWidth,
		ScreenHeight,
		sdl.WINDOW_SHOWN,
	)
	if err != nil {
		panic(err)
	}

	a.Renderer, err = sdl.CreateRenderer(a.Window, -1, sdl.RENDERER_ACCELERATED)
	if err != nil {
		panic(err)
	}
}
