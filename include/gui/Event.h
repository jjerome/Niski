namespace Niski
{
	namespace GUI
	{
		class Event
		{
			enum class eventType {
				GainedFocus,
				LostFocus,

			};
		public:
			Event(eventType evtType);
			~Event();

			eventType getEventType() const;

		private:

		};
	}
}