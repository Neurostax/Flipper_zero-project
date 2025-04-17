import DisplayFrame from "./display-frame"

interface SystemInfoProps {
  onBack: () => void
}

export default function SystemInfo({ onBack }: SystemInfoProps) {
  return (
    <DisplayFrame title="System Info" onBack={onBack}>
      <div className="flex flex-col h-full text-[8px]">
        <div className="grid grid-cols-2 gap-x-2 gap-y-1">
          <div>Firmware:</div>
          <div>v0.73.1</div>

          <div>Hardware:</div>
          <div>F7 v3.0</div>

          <div>Battery:</div>
          <div>3.82V (85%)</div>

          <div>SD Card:</div>
          <div>8GB (2.1GB free)</div>

          <div>Uptime:</div>
          <div>2d 7h 15m</div>

          <div>Temperature:</div>
          <div>24.3°C</div>

          <div>Serial:</div>
          <div>F0:0D:CA:FE:BA:BE</div>
        </div>

        <div className="mt-auto text-center">Flipper Zero v2.0</div>
      </div>
    </DisplayFrame>
  )
}
