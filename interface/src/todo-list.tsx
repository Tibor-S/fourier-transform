import { For, createSignal } from 'solid-js';

type Point = { x: number; y: number};

export const PointList = () => {
  let input!: HTMLInputElement;
  const ylim = [-250, 250]
  const speed = 1 // * px per 10ms
  const initPoints: Point[] = []
  for (let x = 0; x < 500; x += 500/1000) {
    let y = 250*Math.sin(2*Math.PI* x/250) - ylim[0]
    initPoints.push({x:x,y:y})
  } 
  const startT = Date.now()
  const [points, setPoints] = createSignal<Point[]>(initPoints);
  const [t, setT] = createSignal<number>(0);
  

  let oldx:number, oldy:number, x:number, y:number = NaN
  
  const update = () => {
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

  setInterval(update,10)

  return (
    <>
    <button onClick={update} >jump 1s</button>
    <div>{t}</div>
    <svg width={500} height={ylim[1]-ylim[0]}>
      <For each={points()}>
        {(point) => {
          x = point.x;
          y = point.y;
          

          if (!isNaN(oldx) && !isNaN(oldy)) {
            const sx = x.toString()
            const sy = y.toString()
            const soldx = oldx.toString()
            const soldy = oldy.toString()
            oldx = x;
            oldy = y;
            return (
              <line x1={soldx} y1={soldy} x2={sx} y2={sy} stroke="black" />
            );
          }
          oldx = x;
          oldy = y;
        }}
      </For>
    </svg>
    </>
  );
};
