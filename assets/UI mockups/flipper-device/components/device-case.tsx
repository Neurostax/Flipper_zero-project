"use client"

import { useRef } from "react"
import { useFrame } from "@react-three/fiber"
import { Text } from "@react-three/drei"
import type * as THREE from "three"

export function DeviceCase() {
  const caseRef = useRef<THREE.Group>(null)

  // Slightly rotate the case for better initial view
  useFrame(() => {
    if (caseRef.current && !caseRef.current.userData.initialized) {
      caseRef.current.rotation.x = 0.2
      caseRef.current.rotation.y = 0.5
      caseRef.current.userData.initialized = true
    }
  })

  return (
    <group ref={caseRef} position={[0, 0, 0]}>
      {/* Main case - positioned further away in the exploded view */}
      <group position={[0, 4, 0]}>
        {/* Bottom case */}
        <mesh castShadow receiveShadow position={[0, 0, 0]}>
          <boxGeometry args={[7, 0.5, 3.5]} />
          <meshStandardMaterial color="#1a1a1a" roughness={0.8} metalness={0.2} />
        </mesh>

        {/* Side walls */}
        <mesh castShadow receiveShadow position={[0, 0.5, 1.75]}>
          <boxGeometry args={[7, 1, 0.2]} />
          <meshStandardMaterial color="#1a1a1a" roughness={0.8} metalness={0.2} />
        </mesh>

        <mesh castShadow receiveShadow position={[0, 0.5, -1.75]}>
          <boxGeometry args={[7, 1, 0.2]} />
          <meshStandardMaterial color="#1a1a1a" roughness={0.8} metalness={0.2} />
        </mesh>

        <mesh castShadow receiveShadow position={[3.5, 0.5, 0]}>
          <boxGeometry args={[0.2, 1, 3.5]} />
          <meshStandardMaterial color="#1a1a1a" roughness={0.8} metalness={0.2} />
        </mesh>

        <mesh castShadow receiveShadow position={[-3.5, 0.5, 0]}>
          <boxGeometry args={[0.2, 1, 3.5]} />
          <meshStandardMaterial color="#1a1a1a" roughness={0.8} metalness={0.2} />
        </mesh>

        {/* USB-C Port */}
        <group position={[3.6, 0.5, 0]}>
          <mesh castShadow receiveShadow>
            <boxGeometry args={[0.1, 0.3, 0.8]} />
            <meshStandardMaterial color="#333333" />
          </mesh>
          <Text position={[0.5, 0, 0]} rotation={[0, -Math.PI / 2, 0]} fontSize={0.2} color="orange">
            USB-C
          </Text>
        </group>

        {/* GPIO Port */}
        <group position={[0, 0.5, 1.85]}>
          <mesh castShadow receiveShadow>
            <boxGeometry args={[1.5, 0.3, 0.1]} />
            <meshStandardMaterial color="#333333" />
          </mesh>
          <Text position={[0, 0.5, 0]} fontSize={0.2} color="orange">
            GPIO
          </Text>
        </group>

        {/* Side Buttons */}
        <group position={[-3.6, 0.5, 0]}>
          <mesh castShadow receiveShadow position={[0, 0.3, 0.5]}>
            <boxGeometry args={[0.1, 0.2, 0.4]} />
            <meshStandardMaterial color="orange" />
          </mesh>
          <mesh castShadow receiveShadow position={[0, 0.3, -0.5]}>
            <boxGeometry args={[0.1, 0.2, 0.4]} />
            <meshStandardMaterial color="orange" />
          </mesh>
          <Text position={[-0.5, 0.3, 0]} rotation={[0, Math.PI / 2, 0]} fontSize={0.2} color="orange">
            Buttons
          </Text>
        </group>
      </group>

      {/* Top case - positioned further away in the exploded view */}
      <group position={[0, -4, 0]}>
        {/* Top case with screen cutout */}
        <mesh castShadow receiveShadow>
          <boxGeometry args={[7, 0.5, 3.5]} />
          <meshStandardMaterial color="#1a1a1a" roughness={0.8} metalness={0.2} />
        </mesh>

        {/* Screen cutout */}
        <mesh position={[-1, 0.3, 0]}>
          <boxGeometry args={[3, 0.2, 2]} />
          <meshStandardMaterial color="#111111" />
        </mesh>

        {/* D-pad */}
        <group position={[2, 0.3, 0]}>
          <mesh castShadow receiveShadow>
            <boxGeometry args={[0.6, 0.1, 0.6]} />
            <meshStandardMaterial color="#333333" />
          </mesh>
          <mesh castShadow receiveShadow position={[0, 0.1, 0.7]}>
            <boxGeometry args={[0.6, 0.1, 0.6]} />
            <meshStandardMaterial color="orange" />
          </mesh>
          <mesh castShadow receiveShadow position={[0.7, 0.1, 0]}>
            <boxGeometry args={[0.6, 0.1, 0.6]} />
            <meshStandardMaterial color="orange" />
          </mesh>
          <mesh castShadow receiveShadow position={[0, 0.1, -0.7]}>
            <boxGeometry args={[0.6, 0.1, 0.6]} />
            <meshStandardMaterial color="orange" />
          </mesh>
          <mesh castShadow receiveShadow position={[-0.7, 0.1, 0]}>
            <boxGeometry args={[0.6, 0.1, 0.6]} />
            <meshStandardMaterial color="orange" />
          </mesh>
        </group>

        {/* MicroSD slot */}
        <group position={[0, 0, -1.85]}>
          <mesh castShadow receiveShadow>
            <boxGeometry args={[1, 0.2, 0.1]} />
            <meshStandardMaterial color="#333333" />
          </mesh>
          <Text position={[0, 0.5, 0]} fontSize={0.2} color="orange">
            microSD
          </Text>
        </group>
      </group>
    </group>
  )
}
