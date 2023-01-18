import { createConnection, NetConnectOpts, Socket } from "net";
import { createSignal } from "solid-js";


export const SocketEl = () => {
  const [socket, setSocket] = createSignal<Socket>()
  let host = '127.0.0.1'
  let port = 5000
  let timeout = 10000
  

  return <button
    onClick={() => connect({
      host: host,
      port: port,
      timeout: timeout,
    })}
  >Connect</button>
} 

const connect = (options: NetConnectOpts, callback?: (sck:Socket) => void) => {
  const sck = createConnection(options)
  console.log('connected')
  if (callback !== undefined) callback(sck)
}
