package graphics

import (
	"Lunarisnia/sdl-pong/internal/dsu"
	"github.com/veandco/go-sdl2/img"
	"github.com/veandco/go-sdl2/sdl"
)

func PrepareScene(r *sdl.Renderer) {
	r.SetDrawColor(96, 128, 255, 255)
	r.Clear()
}

func PresentScene(r *sdl.Renderer) {
	r.Present()
}

func LoadTexture(r *sdl.Renderer, filename string) (*sdl.Texture, error) {
	sdl.LogMessage(sdl.LOG_CATEGORY_APPLICATION, sdl.LOG_PRIORITY_INFO, "Loading %s", filename)
	texture, err := img.LoadTexture(r, filename)
	if err != nil {
		return nil, err
	}

	return texture, nil
}

func Blit(r *sdl.Renderer, texture *sdl.Texture, position dsu.Vector2i) error {
	dest := sdl.Rect{
		X: position.X,
		Y: position.Y,
	}
	_, _, width, height, err := texture.Query()
	if err != nil {
		return err
	}
	dest.W = width
	dest.H = height

	err = r.Copy(texture, nil, &dest)
	if err != nil {
		return err
	}

	return nil
}
