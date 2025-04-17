export default function StatusBar() {
  const currentTime = new Date().toLocaleTimeString([], { hour: "2-digit", minute: "2-digit" })

  return (
    <div className="flex justify-between items-center text-[8px] border-b border-[#00FFFF] px-1">
      <div>SD:2.1GB</div>
      <div>{currentTime}</div>
      <div className="flex items-center">
        <span className="mr-1">85%</span>
        <div className="w-4 h-2 border border-[#00FFFF] relative">
          <div className="absolute top-0 left-0 bottom-0 bg-[#00FFFF] w-[85%]"></div>
        </div>
      </div>
    </div>
  )
}
