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

	// at most one of these three is set
	checkedInAt?: IDateTime // checked in, not checked out
	checkedOutAt?: IDateTime // checked out, WAITING for cleaning
	cleanStartedAt?: IDateTime // cleaning started, not finished
	// if all 3 are undefined, the room is free

	occupation?: number
	nDays?: number
}

const paidEvents: {
	dateTime: IDateTime
	amount: number
}[] = []

const roomById: Record<IRoomId, IRoom> = {}
const customerOccupiedRoom: Record<ICustomerId, IRoom> = {}
const allCustomerIds = new Set<ICustomerId>()

const compareDateTime = (a: IDateTime, b: IDateTime) => {
	if (a.date !== b.date) return a.date - b.date
	return a.time - b.time
}

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

	if (room.checkedOutAt || room.cleanStartedAt) {
		console.log(`${prefix}ERROR: ${roomId} is being cleaned.`)
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

const cleaningEvents: {
	dateTime: IDateTime
	message: string
	room: IRoom
}[] = []

const scheduleCleaningEvent = (
	date: number,
	time: ITime,
	room: IRoom
) => {
	room.cleanStartedAt = {date, time}
	console.log(`${outputPrefix(date, time)}A cleaner is assigned to ${room.id}.`)
	const cleanedDateTime = addTime({date, time}, 30)
	cleaningEvents.push({
		message: `${outputPrefix(cleanedDateTime.date, cleanedDateTime.time)}${room.id} has been cleaned.`,
		dateTime: cleanedDateTime,
		room,
	})
}

const checkOut = (
	date: number,
	time: ITime,
	customerId: ICustomerId,
	roomId: IRoomId,
	nStaffs: number,
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
	paidEvents.push({
		dateTime: {date, time},
		amount: total,
	})

	delete customerOccupiedRoom[customerId]
	delete room.checkedInAt
	if (cleaningEvents.length === nStaffs) {
		room.checkedOutAt = {date, time}
		console.log(`${prefix}No cleaner is available.`)
		return
	}

	scheduleCleaningEvent(date, time, room)
}

const checkStatus = (
	date: number,
	time: ITime,
) => {
	let vacantRooms = 0
	let occupiedRooms = 0
	let cleaningRooms = 0
	for (const room of Object.values(roomById)) {
		if (room.checkedInAt) occupiedRooms++
		else if (room.cleanStartedAt || room.checkedOutAt) cleaningRooms++
		else vacantRooms++
	}
	console.log(`${outputPrefix(date, time)}Vacant: ${vacantRooms}, Cleaning in progress: ${cleaningRooms}, Occupied: ${occupiedRooms}`)
}

const sales = (
	date: number,
	time: ITime,
	start: IDateTime,
	end: IDateTime
) => {
	let total = 0
	for (const {dateTime, amount} of paidEvents) {
		if (compareDateTime(start, dateTime) <= 0 && compareDateTime(dateTime, end) < 0) {
			total += amount
		}
	}
	console.log(`${outputPrefix(date, time)}Sales: ${total}`)
}

const checkCleaningEvents = (date: number, time: ITime) => {
	const toFinish = cleaningEvents.filter(({dateTime}) => compareDateTime(dateTime, {date, time}) <= 0)
	cleaningEvents.splice(0, toFinish.length)
	for (const {message, room, dateTime} of toFinish) {
		delete room.cleanStartedAt
		console.log(message)

		const waitingForCleaningRooms = Object.values(roomById).filter(room => room.checkedOutAt).sort((a, b) => {
			if (a.category !== b.category) return a.category === RoomCategory.high ? -1 : 1
			if (a.checkedOutAt!.date !== b.checkedOutAt!.date) return a.checkedOutAt!.date - b.checkedOutAt!.date
			return a.checkedOutAt!.time - b.checkedOutAt!.time
		})
		for (const room of waitingForCleaningRooms.slice(0, 1)) {
			delete room.checkedOutAt
			scheduleCleaningEvent(dateTime.date, dateTime.time, room)
		}
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
		checkCleaningEvents(date, time)
		switch (code) {
			case 'check-in': {
				const [customerId, roomId, capacityStr, nDaysStr] = request
				checkIn(date, time, customerId, roomId, +capacityStr, +nDaysStr)
			}
				break
			case 'check-out': {
				const [customerId, roomId] = request
				checkOut(date, time, customerId, roomId, nStaffs)
			}
				break
			case 'status':
				checkStatus(date, time)
				break
			case 'sales':
				const [startDate, startTime, endDate, endTime] = request
				sales(
					date,
					time,
					{
						date: +startDate,
						time: timeFromStr(startTime)
					},
					{
						date: +endDate,
						time: timeFromStr(endTime)
					}
				)
				break
			default:
				throw new Error(`Unknown code: ${code}`)
		}
	}
	while (cleaningEvents.length) checkCleaningEvents(cleaningEvents[cleaningEvents.length - 1].dateTime.date, cleaningEvents[cleaningEvents.length - 1].dateTime.time)
}

main()

