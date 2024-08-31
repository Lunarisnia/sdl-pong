package dsu

import "github.com/veandco/go-sdl2/sdl"

type Entity struct {
	Position Vector2i
	Texture  *sdl.Texture
}
