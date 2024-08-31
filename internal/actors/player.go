package actors

import (
	"fmt"

	"Lunarisnia/sdl-pong/internal/core"
	"Lunarisnia/sdl-pong/internal/dsu"
	"Lunarisnia/sdl-pong/internal/graphics"
	"github.com/veandco/go-sdl2/sdl"
)

func NewPlayer(a *core.App, position dsu.Vector2i, texture *sdl.Texture) *Player {
	player := Player{
		Position: position,
		Texture:  texture,
	}
	a.RegisterNode(&player)

	return &player
}

type Player struct {
	Position dsu.Vector2i
	Texture  *sdl.Texture
}

func (p *Player) OnStart() {
	fmt.Println("This start")
}

func (p *Player) OnUpdate() {
	// fmt.Println("Updated")
}

func (p *Player) OnRender(r *sdl.Renderer) {
	graphics.Blit(r, p.Texture, p.Position, 10.0)
}

func (p *Player) OnKeyDown(key *sdl.KeyboardEvent) {
	fmt.Println("Keydown: ", key.Keysym.Scancode)
	p.Position = p.Position.Add(dsu.Vector2i{X: 10, Y: 0})
}

func (p *Player) OnKeyUp(key *sdl.KeyboardEvent) {
	fmt.Println("KeyUp: ", key.Keysym.Scancode)
}
