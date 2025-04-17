"use client"

import { Suspense } from "react"
import { Canvas } from "@react-three/fiber"
import { OrbitControls, Environment, PerspectiveCamera } from "@react-three/drei"
import { DeviceCase } from "./device-case"
import { InternalComponents } from "./internal-components"

export default function FlipperDevice() {
  return (
    <div className="w-full h-screen bg-gray-900">
      <Canvas shadows>
        <PerspectiveCamera makeDefault position={[0, 0, 20]} fov={40} />
        <ambientLight intensity={0.5} />
        <spotLight position={[10, 10, 10]} angle={0.15} penumbra={1} intensity={1} castShadow />
        <Suspense fallback={null}>
          <DeviceCase />
          <InternalComponents />
          <Environment preset="city" />
        </Suspense>
        <OrbitControls enablePan={true} enableZoom={true} enableRotate={true} minDistance={5} maxDistance={30} />
      </Canvas>
      <div className="absolute bottom-4 left-4 text-white text-sm">
        <p>Matte black and orange Flipper Zero-style device</p>
        <p>Drag to rotate | Scroll to zoom</p>
      </div>
    </div>
  )
}
