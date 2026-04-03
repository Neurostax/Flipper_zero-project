"use client"

import type { ReactNode } from "react"
import StatusBar from "./status-bar"

interface DisplayFrameProps {
  children: ReactNode
  title: string
  showBack?: boolean
  onBack?: () => void
}

export default function DisplayFrame({ children, title, showBack = true, onBack }: DisplayFrameProps) {
  return (
    <div className="w-full h-full bg-black text-[#00FFFF] font-mono text-xs overflow-hidden">
      <StatusBar />

      <div className="border-b border-[#00FFFF] py-1 px-2 flex items-center">
        {showBack && (
          <span className="mr-1 cursor-pointer" onClick={onBack}>
            &lt;
          </span>
        )}
        <span className="text-center flex-1">{title}</span>
      </div>

      <div className="p-1 h-[100px]">{children}</div>
    </div>
  )
}
