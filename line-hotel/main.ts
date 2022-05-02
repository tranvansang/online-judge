type IRoomId = string
type ICustomerId = string
type ITime = number

interface IDateTime {
	date: number
	time: ITime
}

enum RoomCategory {
	low,
	high,
}

interface IRoom {
	id: IRoomId
	capacity: number
	price: number
	category: RoomCategory

	// at most one of these two is set
	cleanStartedAt?: IDateTime
	checkedInAt?: IDateTime
	occupation?: number
	nDays?: number
}

const roomById: Record<IRoomId, IRoom> = {}
const customerOccupiedRoom: Record<ICustomerId, IRoom> = {}
const allCustomerIds = new Set<ICustomerId>()

// minutes from start of the day
const timeFromStr = (str: string) => {
	const [hour, minute] = str.split(':')
	return +hour * 60 + +minute
}
const pad = (n: number) => n < 10 ? `0${n}` : n
const timeToStr = (time: ITime) => `${pad(Math.floor(time / 60))}:${pad(time % 60)}`
const addTime = (dateTime: IDateTime, add: number) => {
	let {date, time} = dateTime
	time += add
	date += Math.floor(time / 24 / 60)
	time %= 24 * 60
	return {date, time}
}

const outputPrefix = (
	date: number,
	time: ITime,
) => `${date} ${timeToStr(time)} `

const checkIn = (
	date: number,
	time: ITime,
	customerId: ICustomerId,
	roomId: IRoomId,
	occupation: number,
	nDays: number,
) => {
	allCustomerIds.add(customerId)

	const prefix = outputPrefix(date, time)

	const room = roomById[roomId]
	if (!room) {
		console.log(`${prefix}ERROR: ${roomId} does not exist.`)
		return
	}

	if (occupation > room.capacity) {
		console.log(`${prefix}ERROR: ${roomId} cannot accommodate ${customerId}.`)
		return
	}

	if (room.cleanStartedAt) {
		`${prefix}ERROR: ${roomId} is being cleaned.`
		return
	}

	if (room.checkedInAt) {
		console.log(`${prefix}ERROR: ${roomId} is occupied.`)
		return
	}

	customerOccupiedRoom[customerId] = room
	room.occupation = occupation
	room.nDays = nDays
	room.checkedInAt = {date, time}
	console.log(`${prefix}${customerId} successfully checked in to ${roomId}.`)
}

const isHoliday = (date: number) => [5, 6].includes((date - 1) % 7)
const calculateTotal = (
	room: IRoom,
	checkInAt: IDateTime,
	occupation: number,
	nDays: number
) => [...Array(nDays)].reduce((acc, _, i) => acc + room.price * (isHoliday(checkInAt.date + 1 + i) ? 1.5 : 1), 0)

const waitingMessages: {
	dateTime: IDateTime
	message: string
}[] = []

const checkOut = (
	date: number,
	time: ITime,
	customerId: ICustomerId,
	roomId: IRoomId,
) => {
	const prefix = outputPrefix(date, time)

	const room = roomById[roomId]
	if (!room) {
		console.log(`${prefix}ERROR: ${roomId} does not exist.`)
		return
	}

	if (!allCustomerIds.has(customerId)) {
		console.log(`${prefix}ERROR: ${customerId} does not exist.`)
		return
	}

	if (!customerOccupiedRoom[customerId]) {
		console.log(`${prefix}ERROR: ${customerId} is not in ${roomId}.`)
		return
	}

	// note: customer may checkout earlier than requested
	const total = calculateTotal(room, room.checkedInAt!, room.occupation!, room.nDays!)
	console.log(`${prefix}${customerId} has to pay ${total} to leave ${roomId}.`)

	delete customerOccupiedRoom[customerId]
	console.log(`${prefix}A cleaner is assigned to ${roomId}.`)

	const cleanedDateTime = addTime({date, time}, 30)
	waitingMessages.push({
		message: `${outputPrefix(cleanedDateTime.date, cleanedDateTime.time)}${roomId} has been cleaned.`,
		dateTime: cleanedDateTime,
	})
	// console.log(`${prefix}No cleaner is available.`)
}

const checkStatus = (
	date: number,
	time: ITime,
) => {
	throw new Error('Not implemented')
}

const sales = (
	date: number,
	time: ITime,
) => {
	throw new Error('Not implemented')
}

const showWaitingMessages = (date: number, time: ITime) => {
	const toShow = waitingMessages.filter(({dateTime}) => dateTime.date < date || dateTime.date === date && dateTime.time <= time)
	waitingMessages.splice(0, toShow.length)
	for (const {message} of toShow) {
		console.log(message)
	}
}

const main = async () => {
	const lines = await new Promise<string[]>(resolve => {
		let data = ''
		process.stdin.resume()
		process.stdin.setEncoding('utf8')

		process.stdin.on('data', d => data += d)
		process.stdin.on('end', () => resolve(data.split('\n')))
	})

	const [nRoomsStr, nStaffsStr] = lines[0].split(' ')
	const nRooms = +nRoomsStr
	const nStaffs = +nStaffsStr

	// room information
	for (const line of lines.slice(1, 1 + nRooms)) {
		const [id, category, capacity, price] = line.split(' ')
		roomById[id] = {
			id,
			category: category === 'LOW' ? RoomCategory.low : RoomCategory.high,
			capacity: +capacity,
			price: +price,
		}
	}

	// process requests
	for (const line of lines.slice(1 + nRooms)) {
		if (line === '') continue
		const [dateStr, timeStr, code, ...request] = line.split(' ')
		const date = +dateStr
		const time = timeFromStr(timeStr)
		showWaitingMessages(date, time)
		switch (code) {
			case 'check-in': {
				const [customerId, roomId, capacityStr, nDaysStr] = request
				checkIn(date, time, customerId, roomId, +capacityStr, +nDaysStr)
			}
				break
			case 'check-out': {
				const [customerId, roomId] = request
				checkOut(date, time, customerId, roomId)
			}
				break
			case 'status':
				checkStatus(date, time)
				break
			case 'sales':
				sales(date, time)
				break
			default:
				throw new Error(`Unknown code: ${code}`)
		}
	}
	for (const {message} of waitingMessages) {
		console.log(message)
	}
	waitingMessages.length = 0
}

main()

