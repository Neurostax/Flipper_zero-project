"use client"

import { Text, Line } from "@react-three/drei"

export function InternalComponents() {
  // Create lines to connect labels to components
  const createConnector = (start: [number, number, number], end: [number, number, number]) => {
    return <Line points={[start, end]} color="orange" lineWidth={1} dashed={true} />
  }

  return (
    <group>
      {/* ESP32 Board */}
      <group position={[0, 0, 0]}>
        <mesh castShadow receiveShadow>
          <boxGeometry args={[4, 0.2, 2.5]} />
          <meshStandardMaterial color="#107a8b" />
        </mesh>
        <mesh castShadow receiveShadow position={[1, 0.15, 0.5]}>
          <boxGeometry args={[1, 0.1, 1]} />
          <meshStandardMaterial color="#333333" />
        </mesh>
        <mesh castShadow receiveShadow position={[-1, 0.15, -0.5]}>
          <boxGeometry args={[1.5, 0.1, 0.8]} />
          <meshStandardMaterial color="#333333" />
        </mesh>
        {createConnector([0, 0.2, 0], [0, 1, 2])}
        <Text position={[0, 1, 2]} fontSize={0.3} color="white">
          ESP32 Board
        </Text>
      </group>

      {/* OLED Screen */}
      <group position={[-1, 1, 0]}>
        <mesh castShadow receiveShadow>
          <boxGeometry args={[3, 0.1, 2]} />
          <meshStandardMaterial color="#111111" />
        </mesh>
        <mesh castShadow receiveShadow position={[0, 0.1, 0]}>
          <boxGeometry args={[2.8, 0.05, 1.8]} />
          <meshStandardMaterial color="#222222" emissive="#0066ff" emissiveIntensity={0.2} />
        </mesh>
        {createConnector([-1, 0.2, 0], [-3, 1, 0])}
        <Text position={[-3, 1, 0]} fontSize={0.3} color="white">
          OLED Screen
        </Text>
      </group>

      {/* IR LED */}
      <group position={[2.5, 0.5, 1.5]}>
        <mesh castShadow receiveShadow>
          <cylinderGeometry args={[0.2, 0.2, 0.3, 16]} />
          <meshStandardMaterial color="#cc0000" emissive="#ff0000" emissiveIntensity={0.5} />
        </mesh>
        {createConnector([2.5, 0.5, 1.5], [4, 1, 2])}
        <Text position={[4, 1, 2]} fontSize={0.3} color="white">
          IR LED
        </Text>
      </group>

      {/* NFC Antenna */}
      <group position={[0, 0.5, -1.5]}>
        <mesh castShadow receiveShadow>
          <torusGeometry args={[0.8, 0.05, 16, 32]} />
          <meshStandardMaterial color="#cccccc" />
        </mesh>
        {createConnector([0, 0.5, -1.5], [2, 1, -2])}
        <Text position={[2, 1, -2]} fontSize={0.3} color="white">
          NFC Antenna
        </Text>
      </group>

      {/* Lithium Battery */}
      <group position={[2, -1, 0]}>
        <mesh castShadow receiveShadow>
          <boxGeometry args={[2.5, 0.5, 2]} />
          <meshStandardMaterial color="#444444" />
        </mesh>
        <mesh castShadow receiveShadow position={[1, 0.3, 0]}>
          <boxGeometry args={[0.3, 0.1, 0.5]} />
          <meshStandardMaterial color="red" />
        </mesh>
        <mesh castShadow receiveShadow position={[1.3, 0.3, 0]}>
          <boxGeometry args={[0.3, 0.1, 0.5]} />
          <meshStandardMaterial color="black" />
        </mesh>
        {createConnector([2, -1, 0], [4, -1, 0])}
        <Text position={[4, -1, 0]} fontSize={0.3} color="white">
          Lithium Battery
        </Text>
      </group>

      {/* MicroSD Slot */}
      <group position={[0, -0.5, -1.5]}>
        <mesh castShadow receiveShadow>
          <boxGeometry args={[1.2, 0.2, 0.8]} />
          <meshStandardMaterial color="#555555" />
        </mesh>
        <mesh castShadow receiveShadow position={[0, 0, -0.4]}>
          <boxGeometry args={[1, 0.1, 0.1]} />
          <meshStandardMaterial color="#333333" />
        </mesh>
        {createConnector([0, -0.5, -1.5], [-2, -1, -2])}
        <Text position={[-2, -1, -2]} fontSize={0.3} color="white">
          MicroSD Slot
        </Text>
      </group>

      {/* Vibration Motor */}
      <group position={[-2, -1, 0]}>
        <mesh castShadow receiveShadow>
          <cylinderGeometry args={[0.4, 0.4, 0.8, 16]} />
          <meshStandardMaterial color="#888888" />
        </mesh>
        <mesh castShadow receiveShadow position={[0, 0.5, 0]} rotation={[Math.PI / 2, 0, 0]}>
          <cylinderGeometry args={[0.1, 0.1, 0.3, 8]} />
          <meshStandardMaterial color="#444444" />
        </mesh>
        {createConnector([-2, -1, 0], [-4, -1, 0])}
        <Text position={[-4, -1, 0]} fontSize={0.3} color="white">
          Vibration Motor
        </Text>
      </group>
    </group>
  )
}
