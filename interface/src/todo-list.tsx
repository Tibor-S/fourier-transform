import { randomInt } from 'mathjs';
import { For, createSignal, createEffect } from 'solid-js';

type Point = { x: number; y: number};

export const PointList = () => {
  let canvas:HTMLCanvasElement|undefined = undefined;
  const ylim = [-250, 250]
  const speed = 1 // * px per 10ms
  const initPoints: Point[] = []
  for (let x = 0; x < 500; x += 500/40000) {
    let y = randomInt(0,ylim[1]-ylim[0])//250*Math.sin(2*Math.PI* x/250) - ylim[0]
    initPoints.push({x:x,y:y})
  } 
  const startT = Date.now()
  const [points, setPoints] = createSignal<Point[]>(initPoints);
  const [t, setT] = createSignal<number>(0);
  
  const updateT = () => {
    const nPoints: Point[] = []
    for (const p of points()) {
      const nx = p.x
      const ny = (p.y+speed)%(ylim[1]-ylim[0])
      const p2:Point = {x:nx, y:ny};
      nPoints.push(p2)
    }
    setPoints(nPoints)
    setT(Math.round((Date.now()-startT)/1000))
  }

  const updateCtx = (canvas:HTMLCanvasElement|undefined, points:Point[]) => {
    if (canvas === undefined) return 0
    const ctx = canvas.getContext("2d")
    if (ctx === null) return 0
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.beginPath()
    let first = true
    for (const p of points) {
      if (first) {
        ctx.moveTo(p.x,p.y)
        first = false
        continue
      }
      ctx.lineTo(p.x, p.y)
    }
    ctx.stroke()
  }


  setInterval(updateT,10)
  createEffect(() => updateCtx(canvas, points()))

  return (
    <>
    <div>{t}</div>
    <canvas ref={canvas} width={500} height={500} />
    </>
  );
};
